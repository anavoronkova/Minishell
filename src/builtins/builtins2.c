/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:06:41 by boiarinov         #+#    #+#             */
/*   Updated: 2024/04/22 20:40:19 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_export_2(t_data *data, char *name, char *value, char *upd)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (env_check(ft_getenv(data, name), data->env[i]) == 0)
		{
			upd = env_upd(data->env[i], value);
			free(data->env[i]);
			data->env[i] = upd;
			return (enverror(0, name, value));
		}
		i++;
	}
	i = 0;
	while (data->env[i] != NULL)
	{
		if (env_check(ft_getenv(data, name), data->env[i]) != 0)
		{
			env_create(data, name, value);
			return (enverror(0, name, value));
		}
		i++;
	}
	return (enverror(0, name, value));
}

int	ft_export(t_cmd *cmd, t_data *data)
{
	int		status;
	char	*name;
	char	*value;
	char	*upd;

	status = 1;
	name = NULL;
	value = NULL;
	upd = NULL;
	status = pre_export(cmd->args[1], &name, &value);
	if (status == 0)
		return (ft_export_2(data, name, value, upd));
	return (enverror(status, name, value));
}

int	ft_unset(t_cmd *cmd, t_data *data)
{
	int		status;
	int		i;
	int		j;

	status = 1;
	i = 0;
	while (data->env[i] != NULL)
	{
		if (env_check(ft_getenv(data, cmd->args[1]), data->env[i]) == 0)
		{
			free(data->env[i]);
			j = i;
			while (data->env[j + 1] != NULL)
			{
				data->env[j] = data->env[j + 1];
				j++;
			}
			data->env[j] = NULL; 
			status = 0;
			break ;
		}
		i++;
	}
	return (enverror(status, NULL, NULL));
}

int	ft_env(t_cmd *cmd, t_data *data, int flag)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!cmd->args[1])
	{
		while (data->env[++i] != NULL)
		{
			if (flag == 2)
				ft_printf("declare -x ");
			ft_printf("%s\n", data->env[i]);
		}
		return (enverror(0, NULL, NULL));
	}
	while (data->env[j] != NULL)
	{
		if (env_check(cmd->args[1], data->env[j]) == 0)
		{
			ft_printf("env '%s': Permission denied\n", cmd->args[1]);
			return (enverror(126, NULL, NULL));
		}
		j++;
	}
	return (enverror(1, NULL, NULL));
}

int	ft_env_sys(t_cmd *cmd, int type, t_data *data)
{
	if (type == 1)
		return (ft_env(cmd, data, 1));
	else
	{
		if (type == 2)
		{
			if (!cmd->args[1])
				return (ft_env(cmd, data, 2));
			else
				return (ft_export(cmd, data));
		}
		else if (type == 3)
		{
			if (!cmd->args[1])
				return (enverror(0, NULL, NULL));
			return (ft_unset(cmd, data));
		}
	}
	return (success);
}
