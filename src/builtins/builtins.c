/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:18:20 by aboiarin          #+#    #+#             */
/*   Updated: 2024/04/28 15:13:14 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_cmd *cmd, t_data *data)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!cmd->args[i])
		return (echerror(status));
	while (cmd->args[i] && is_n(cmd->args[i], &status))
		i++;
	while (cmd->args[i])
	{
		if ((cmd->args[i][0] == '$' && ft_getenv(data, cmd->args[i]))
			|| (cmd->args[i][0] != '$') || (ft_strcmp(cmd->args[i], "$") == 0))
		{
			ft_printf("%s", cmd->args[i]);
			if (cmd->args[i + 1] != NULL)
				ft_printf(" ");
		}
		i++;
	}
	return (echerror(status));
}

int	ft_cd2(t_cmd *cmd, char *home, char *temp)
{
	if (ft_strcmp(cmd->args[1], "$HOME") == 0 && home != NULL)
	{
		if (chdir(home) == 0)
		{
			temp = ft_strdup(&cmd->args[1][2]);
			if (chdir(temp) == 0)
				return (cderror(temp, 3));
			return (cderror(temp, 4));
		}
	}
	else if (ft_strcmp(cmd->args[1], "$HOME") == 0 && home == NULL)
		return (cderror(NULL, 2));
	else if (ft_strcmp(cmd->args[1], "$HOME") != 0)
	{
		if (chdir(cmd->args[1]) == 0)
			return (cderror(NULL, 0));
	}
	return (cderror(NULL, 1));
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	char	*home;
	char	*temp;

	home = NULL;
	temp = NULL;
	home = ft_getenv(data, "HOME");
	if (cmd->args[1] && cmd->args[2])
		return (cderror(NULL, 5));
	if (!cmd->args[1] || (ft_strcmp(cmd->args[1], "~") == 0))
	{
		if (home == NULL)
			return (cderror(NULL, 2));
		else if (chdir(home) == 0)
			return (cderror(NULL, 0));
	}
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		temp = ft_getenv(data, "OLDPWD");
		if (chdir(temp) == 0)
			return (cderror(NULL, 0));
	}
	else
		return (ft_cd2(cmd, home, temp));
	return (cderror(NULL, 1));
}

int	ft_pwd(t_cmd *cmd)
{
	char	pwd[4096];
	int		i;

	i = 1;
	if (cmd->args[1])
	{
		while (cmd->args[i])
		{
			if (ft_strchr(cmd->args[i], '-') != 0)
			{
				ft_printf("Error: pwd options are not handled\n");
				return (1);
			}
			i++;
		}
	}
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		ft_printf("%s\n", pwd);
		return (0);
	}
	return (nferr);
}

int	ft_exit(t_cmd *cmd, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (!cmd->args[1])
		exit_minishell(data, data->exit_status);
	exit_code = ft_atoi(cmd->args[1]);
	if (!exit_code)
	{
		if (ft_strcmp(cmd->args[1], "+") == 0)
			return (100);
		else if (ft_strcmp(cmd->args[1], "-") == 0)
			return (156);
		exit_minishell(data, handle_error("exit",
				"numeric argument required", 2));
	}
	else
	{
		if (cmd->args[2])
			exit_minishell(data, handle_error("exit",
					"too many arguments", 1));
		exit_minishell(data, exit_code);
	}
	exit_minishell(data, 1);
	return (success);
}
