/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:04:33 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/22 20:17:36 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_builtin_command(const char *cmd)
{
	int			i;
	const char	*builtins[8]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	i = 0;
	while (builtins[i])
	{
		if (!strcmp(builtins[i], cmd))
			return (true);
		i++;
	}
	return (false);
}

int	count_commands(t_cmd *command)
{
	t_cmd	*temp;
	int		i;

	i = 0;
	temp = command;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	manage_std_save(t_data *data, int flag)
{
	if (flag == SAVE_FD)
	{
		data->stdin_save = dup(STDIN_FILENO);
		data->stdout_save = dup(STDOUT_FILENO);
	}
	else if (flag == RESTORE_FD)
	{
		if (dup2(data->stdin_save, STDIN_FILENO) == -1
			|| dup2(data->stdout_save, STDOUT_FILENO) == -1)
		{
			perror("Failed to update stdin or stdout\n");
			exit_minishell(data, EXIT_FAILURE);
		}
	}
	else if (flag == CLOSE_FD)
	{
		if (dup2(data->stdin_save, STDIN_FILENO) == -1
			|| dup2(data->stdout_save, STDOUT_FILENO) == -1)
		{
			perror("Failed to update stdin or stdout\n");
			exit_minishell(data, EXIT_FAILURE);
		}
		close(data->stdin_save);
		close(data->stdout_save);
	}
}

int	create_pipe(t_pipe	*pd)
{
	if (pipe(pd->pipefd) == -1)
	{
		free(pd->pids);
		return (handle_error(NULL, "Error: failed to create a pipe", ferr));
	}
	return (success);
}

int	init_pipeline(t_cmd *cmd, pid_t **pids)
{
	*pids = malloc(sizeof(pid_t) * count_commands(cmd));
	if (!*pids)
		return (handle_error(NULL, "Failed to malloc for PIDs", ferr));
	return (success);
}
