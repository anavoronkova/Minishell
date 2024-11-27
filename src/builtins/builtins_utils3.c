/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:25:03 by aboiarin          #+#    #+#             */
/*   Updated: 2024/04/22 21:41:49 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	echerror(int status)
{
	if (status == 0)
		ft_printf("\n");
	return (status);
}

void	env_create(t_data *data, char *name, char *value)
{
	char	**temp;
	char	*add;
	int		size;

	size = ft_arrlen(data->env) + 1;
	temp = (char **)malloc(sizeof(char *) * (size + 1));
	temp = env_copy(data->env, temp);
	add = ft_envdup(name);
	temp[size - 1] = ft_strjoin(add, value);
	temp[size] = NULL;
	free_arr(data->env);
	data->env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!data->env)
		return ;
	data->env = env_copy(temp, data->env);
	data->env[size] = NULL;
	free_arr(temp);
	free(add);
}

int	pre_export(char *input, char **name, char **value)
{
	char	*equal_sign_pos;
	size_t	len;

	if ((ft_strcmp(input, "=") == 0 || ft_atoi(input))
		|| ((ft_strchr(input, '-') != NULL) && ft_strchr(input, '=') == NULL))
		return (4);
	equal_sign_pos = ft_strchr(input, '=');
	if (!equal_sign_pos)
		return (3);
	len = equal_sign_pos - input;
	*name = malloc(len + 1);
	if (!*name)
		return (3);
	ft_strncpy(*name, input, len);
	(*name)[len] = '\0';
	if (ft_strchr(*name, '-') != NULL)
		return (4);
	*value = ft_strdup(equal_sign_pos + 1);
	if (!*value || ft_strchr(*value, '-') != NULL)
	{
		free(*name);
		*name = NULL;
		return (3);
	}
	return (success);
}
