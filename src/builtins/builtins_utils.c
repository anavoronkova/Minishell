/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:16:19 by aboiarin          #+#    #+#             */
/*   Updated: 2024/04/22 20:41:30 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

bool	is_n(const char *arg, int *status)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (false);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	*status = 1;
	return (true);
}

int	cderror(char *temp, int status)
{
	if (status == 1)
		return (handle_error("cd", "No such file or directory", status));
	if (status == 2)
		return (handle_error("cd", "home is not set", 1));
	if (status == 3 && temp != NULL)
	{
		free(temp);
		status = 0;
	}
	if (status == 4 && temp != NULL)
	{
		free(temp);
		status = 1;
	}
	if (status == 5)
		return (handle_error("cd", "too many arguments", 1));
	return (status);
}
