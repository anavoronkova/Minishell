/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:58:04 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/29 15:41:25 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getenv(t_data *data, const char *env_name)
{
	int		i;
	size_t	name_len;

	i = 0;
	if (env_name[i] == '$')
		env_name++;
	name_len = ft_strlen(env_name);
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], env_name, name_len)
			&& data->env[i][name_len] == '=')
			return (&data->env[i][name_len + 1]);
		i++;
	}
	return (NULL);
}

char	*expand_tilda(t_data *data, char *env_name)
{
	char	*value;
	char	*expanded_path;
	int		len;

	value = ft_getenv(data, "HOME");
	if (!value)
		value = "$HOME";
	len = ft_strlen(value) + ft_strlen(env_name + 1) + 1;
	if (env_name[1] == '/' || env_name[1] == '\0')
	{
		expanded_path = malloc(ft_strlen(value) + ft_strlen(env_name) + 1);
		if (!expanded_path)
			return (NULL);
		ft_strlcpy(expanded_path, value, ft_strlen(value) + 1);
		ft_strlcat(expanded_path, env_name + 1, len);
		return (expanded_path);
	}
	else
		return (value);
}

char	*expand_env_variable(t_data *data, char *env_name)
{
	char	*value;
	char	*temp;

	if (!ft_strcmp(env_name, "$?"))
	{
		temp = ft_itoa(data->exit_status);
		value = ft_strdup(temp);
		free(temp);
	}
	else if (env_name[0] == '~')
		return (expand_tilda(data, env_name));
	else
	{
		temp = ft_getenv(data, env_name);
		if (!temp)
			return (NULL);
		value = ft_strdup(temp);
	}
	return (value);
}

void	handle_env(t_data *data, t_cmd *command, int *ac, t_token *token)
{
	char	*expanded_value;

	expanded_value = expand_env_variable(data, token->value);
	if (expanded_value)
	{
		decide_if_join(command, token, expanded_value, ac);
		free(expanded_value);
	}
}

char	*handle_quoted_env(t_data *data, t_token *token, char **quoted_string)
{
	char	*expanded_value;
	char	*temp;

	temp = NULL;
	expanded_value = expand_env_variable(data, token->value);
	if (expanded_value)
	{
		temp = ft_strjoin(*quoted_string, expanded_value);
		free(expanded_value);
		free(*quoted_string);
		return (temp);
	}
	return (NULL);
}
