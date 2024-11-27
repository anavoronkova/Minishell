/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:00:44 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/26 18:20:01 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_built_in(t_cmd *cmd, t_data *data)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd, data));
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd, data));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd(cmd));
	if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env_sys(cmd, 1, data));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_env_sys(cmd, 2, data));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_env_sys(cmd, 3, data));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd, data));
	else
		return (nferr);
}

int	execute_single_command(t_cmd *cmd, t_data *data)
{
	if (is_builtin_command(cmd->args[0]))
		return (execute_built_in(cmd, data));
	else if (!ft_strncmp(cmd->args[0], "./", 2)
		|| cmd->args[0][0] == '/' || !ft_strncmp(cmd->args[0], "../", 3))
		return (execute_path(data, cmd));
	else
		return (execute_execve(data, cmd));
}

int	execute_command(t_cmd *cmd, t_data *data)
{
	int	out_fd;
	int	in_fd;
	int	result;

	result = 0;
	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	while (cmd && !cmd->next && (!cmd->args[0]
			|| is_builtin_command(cmd->args[0])))
	{
		result = execute_redir(data, cmd, &in_fd, &out_fd);
		if (result)
			break ;
		if (in_fd && dup2(in_fd, STDIN_FILENO) == -1)
			result = nferr;
		if (cmd->args[0] && is_builtin_command(cmd->args[0]))
			result = execute_built_in(cmd, data);
		break ;
	}
	if (cmd->args[0] && (cmd->next || !is_builtin_command(cmd->args[0])))
		result = execute_pipeline(cmd, data);
	set_exit_status(data, result, 1);
	close(in_fd);
	close(out_fd);
	return (data->exit_status);
}

int	executor(t_cmd *command, t_data *data)
{
	int	result;

	result = 0;
	if (!command)
		return (success);
	else if (!command->args[0] && !command->output
		&& !command->input && !command->heredoc_delimiter)
		return (success);
	manage_std_save(data, SAVE_FD);
	result = execute_command(command, data);
	manage_std_save(data, CLOSE_FD);
	return (result);
}
