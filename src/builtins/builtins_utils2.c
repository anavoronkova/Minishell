/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:25:03 by aboiarin          #+#    #+#             */
/*   Updated: 2024/04/22 20:42:34 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	enverror(int status, char *name, char *value)
{
	if (status == 1)
		return (0);
	if (status == 0 || status == 3 || status == 4)
	{
		if (name != NULL)
			free(name);
		if (value != NULL)
			free(value);
		if (status == 4)
			return (handle_error("export", "not a valid identifier", 1));
		status = 0;
	}
	return (status);
}

char	**env_copy(char **environ, char **env)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	*env_upd(char *env, char *upd)
{
	char	*temp;
	int		i;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	i++;
	temp = malloc(i + ft_strlen(upd) + 1);
	if (!temp)
	{
		printf("Failed to allocate memory for environment update.\n");
		return (NULL);
	}
	temp = ft_strncpy(temp, env, i);
	temp[i] = '\0';
	ft_strlcat(temp, upd, i + ft_strlen(upd) + 1);
	return (temp);
}

int	env_check(char *to_find, char *env)
{
	char	*temp;
	int		status;

	status = 1;
	temp = NULL;
	if (to_find == NULL)
		return (status);
	temp = ft_strchr(env, '=');
	temp++;
	if (temp != NULL)
		status = ft_strcmp(temp, to_find);
	return (status);
}

char	*ft_envdup(const char *s)
{
	char	*dest;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s[size])
		size++;
	dest = (char *)malloc(sizeof(char) * (size + 2));
	if (dest == 0)
		return (0);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '=';
	dest[i + 1] = '\0';
	return (dest);
}
