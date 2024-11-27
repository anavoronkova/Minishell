/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:30:48 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/26 18:20:14 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	finalize_pipeline(pid_t *pids, int count)
{
	int	status;
	int	final_status;
	int	j;

	status = 0;
	final_status = 0;
	j = 0;
	while (j < count)
	{
		waitpid(pids[j], &status, 0);
		if (WIFEXITED(status))
			final_status = WEXITSTATUS(status);
		j++;
	}
	free(pids);
	pids = NULL;
	return (final_status);
}

void	handle_parent_process(t_cmd *cmd, t_pipe *pd)
{
	close(pd->pipefd[1]);
	if (pd->in_fd)
		close(pd->in_fd);
	if (cmd)
		pd->in_fd = pd->pipefd[0];
}

void	handle_child_process(t_pipe *pd, t_cmd *cmd, t_data *data)
{
	int	status;

	status = 0;
	if (cmd->output)
		pd->pipefd[1] = pd->out_fd;
	if (cmd->next)
		dup2(pd->pipefd[1], STDOUT_FILENO);
	close(pd->pipefd[1]);
	if (pd->in_fd)
		dup2(pd->in_fd, STDIN_FILENO);
	if (pd->in_fd && cmd->next)
		close(pd->in_fd);
	close(pd->pipefd[0]);
	status = execute_single_command(cmd, data);
	close(data->stdin_save);
	close(data->stdout_save);
	close(pd->in_fd);
	close(pd->out_fd);
	free(pd->pids);
	free_data(data, 1);
	rl_clear_history();
	exit(status);
}

int	fork_and_execute(t_pipe	*pd, t_cmd *cmd, t_data *data)
{
	if (execute_redir(data, cmd, &pd->in_fd, &pd->out_fd))
	{
		close(pd->pipefd[0]);
		close(pd->pipefd[1]);
		handle_parent_process(cmd, pd);
		if (!cmd->next)
			free(pd->pids);
		return (nferr);
	}
	pd->pid = fork();
	if (pd->pid == -1)
		exit_minishell(data, handle_error(NULL, "Failed to fork", ferr));
	else if (pd->pid == 0)
		handle_child_process(pd, cmd, data);
	else
	{
		pd->pids[pd->i++] = pd->pid;
		handle_parent_process(cmd, pd);
	}
	return (success);
}

int	execute_pipeline(t_cmd *cmd, t_data *data)
{
	t_pipe	pd;
	int		result;

	pd.i = 0;
	pd.in_fd = STDIN_FILENO;
	pd.out_fd = STDOUT_FILENO;
	result = 0;
	if (init_pipeline(cmd, &pd.pids) == -1)
		return (ferr);
	while (cmd)
	{
		if (create_pipe(&pd) == -1)
			return (ferr);
		result = fork_and_execute(&pd, cmd, data);
		if (!cmd->next && result)
			break ;
		manage_std_save(data, RESTORE_FD);
		cmd = cmd->next;
	}
	if (!result)
		result = finalize_pipeline(pd.pids, pd.i);
	if (pd.in_fd)
		close(pd.in_fd);
	return (result);
}
