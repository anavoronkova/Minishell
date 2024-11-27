/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:18:23 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/24 21:34:49 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_full_path(const char *directory, const char *filename)
{
	size_t	dir_len;
	size_t	file_len;
	size_t	total_length;
	char	*full_path;

	if (!directory || !filename)
		return (NULL);
	dir_len = ft_strlen(directory);
	file_len = ft_strlen(filename);
	total_length = dir_len + 1 + file_len + 1;
	full_path = malloc(total_length);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, directory, total_length);
	if (directory[dir_len - 1] != '/')
		ft_strlcat(full_path, "/", total_length);
	ft_strlcat(full_path, filename, total_length);
	return (full_path);
}

int	try_external_cmd(t_data *data, char **paths, t_cmd *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = create_full_path(paths[i], cmd->args[0]);
		if (!full_path)
			return (handle_error(cmd->args[0],
					"Failed to allocate path", nferr));
		if (execve(full_path, cmd->args, data->env) != -1)
		{
			free(full_path);
			return (success);
		}
		free(full_path); 
		i++;
	}
	return (nferr);
}

int	execute_execve(t_data *data, t_cmd *cmd)
{
	char	*path_env;
	char	**paths;
	int		exec_status;

	path_env = ft_getenv(data, "PATH");
	if (!path_env)
		return (handle_error(cmd->args[0],
				"Failed to find $PATH variable", nferr));
	paths = ft_split(path_env, ':');
	if (!paths)
		return (nferr);
	exec_status = try_external_cmd(data, paths, cmd);
	free_arr(paths);
	if (exec_status == success)
		return (success);
	return (handle_error(cmd->args[0], "command not found", 127));
}

int	execute_path(t_data *data, t_cmd *cmd)
{
	struct stat	st;

	if (stat(cmd->args[0], &st) == 0 && (st.st_mode & S_IXUSR))
	{
		if (execve(cmd->args[0], cmd->args, data->env) != -1)
			return (success);
		else
			return (handle_error(cmd->args[0],
					"Is a directory", 126));
	}
	else if (access(cmd->args[0], W_OK) == -1
		&& access(cmd->args[0], F_OK) != -1)
		return (handle_error(cmd->args[0], "Permission denied", 126));
	else
		return (handle_error(cmd->args[0],
				"No such file or directory", 127));
}
