/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:00:01 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/22 11:12:43 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_prompt(void)
{
	char		cwd[1024];
	const char	*suffix;
	char		*prompt;
	size_t		len;

	suffix = "\033[35m minishell> \033[0m";
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return (NULL);
	}
	len = ft_strlen(cwd) + ft_strlen(suffix) + 1;
	prompt = malloc(len);
	if (prompt == NULL)
	{
		perror("Failed to allocate prompt string\n");
		return (NULL);
	}
	ft_strlcpy(prompt, cwd, len);
	ft_strlcat(prompt, suffix, len);
	return (prompt);
}

int	handle_error(const char *subject, char *message, t_exs error_code)
{
	if (subject)
	{
		write(STDERR_FILENO, subject, ft_strlen(subject));
		write(STDERR_FILENO, ": ", 2);
	}
	if (message)
	{
		write(STDERR_FILENO, message, ft_strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
	return (error_code);
}

int	init_data_env(t_data *data)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
		i++;
	data->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		return (nferr);
	data->env = env_copy(environ, data->env);
	if (!data->env)
		return (nferr);
	return (success);
}

void	set_exit_status(t_data *data, int result, int flag)
{
	if (g_signal_received)
	{
		data->exit_status = g_signal_received;
		g_signal_received = 0;
	}
	else if (flag)
		data->exit_status = result;
}
