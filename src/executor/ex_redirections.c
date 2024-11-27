/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 21:59:48 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/26 18:20:20 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_output(char **o_fn, int append, int *out_fd)
{
	int	flags;
	int	file_out;
	int	i;

	file_out = -1;
	flags = O_WRONLY | O_CREAT;
	i = 0;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	while (o_fn[i])
	{
		if (access(o_fn[i], F_OK) != -1 && access(o_fn[i], W_OK) == -1)
			return (handle_error(o_fn[i], "Permission denied", nferr));
		file_out = open(o_fn[i], flags, 0644);
		if (file_out == -1 || dup2(file_out, STDOUT_FILENO) == -1)
		{
			close(file_out);
			return (handle_error(NULL, "Failed to open output file", nferr));
		}
		*out_fd = file_out;
		i++;
	}
	return (success);
}

int	execute_heredoc(const char *hc, int *in_fd)
{
	const char	*tmp;
	int			her_fd;

	tmp = "/tmp/minishell_heredoc";
	her_fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (her_fd == -1 || write(her_fd, hc, ft_strlen(hc)) == -1)
	{
		close(her_fd);
		return (handle_error(NULL,
				"Failed to open or write to a heredoc temp file", nferr));
	}
	close(her_fd);
	her_fd = open(tmp, O_RDONLY);
	if (her_fd == -1 || dup2(her_fd, STDIN_FILENO) == -1)
	{
		close(her_fd);
		return (handle_error(NULL, "Failed to set heredoc as STDIN", nferr));
	}
	*in_fd = her_fd;
	return (success);
}

int	execute_input(char **i_fn, int *in_fd)
{
	int	file_in;
	int	i;

	i = 0;
	while (i_fn[i])
	{
		if (access(i_fn[i], F_OK) != -1)
		{
			if (access(i_fn[i], R_OK) == -1)
				return (handle_error(i_fn[i], "Permission denied", nferr));
		}
		else
			return (handle_error(i_fn[i],
					"No such file or directory", nferr));
		file_in = open(i_fn[i], O_RDONLY);
		if (file_in == -1 || dup2(file_in, STDIN_FILENO) == -1)
		{
			close(file_in);
			return (handle_error(NULL, "Failed to open input file", nferr));
		}
		*in_fd = file_in;
		i++;
	}
	return (success);
}

int	execute_redir(t_data *data, t_cmd *command, int *in_fd, int *out_fd)
{
	int	result;

	result = 0;
	if (command->heredoc)
		result = process_h_input(command);
	if (command->h_input)
		result = execute_heredoc(command->h_input, in_fd);
	if (command->input)
		result = execute_input(command->input, in_fd);
	if (command->output)
		result = execute_output(command->output, command->append, out_fd);
	if (result)
		manage_std_save(data, RESTORE_FD);
	return (result);
}
