/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:49:34 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/29 18:10:31 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*append_input(char *original, const char *to_append)
{
	size_t	original_len;
	size_t	new_len;
	char	*new_input;

	original_len = 0;
	if (!to_append)
		return (original);
	if (original)
		original_len = ft_strlen(original);
	new_len = original_len + ft_strlen(to_append) + 2;
	new_input = malloc(new_len);
	if (!new_input)
		return (NULL);
	if (original)
	{
		ft_strlcpy(new_input, original, original_len + 1);
		free(original);
	}
	else
		new_input[0] = '\0';
	ft_strlcat(new_input, to_append, new_len);
	ft_strlcat(new_input, "\n", new_len);
	return (new_input);
}

bool	handle_empty_pipe(t_data *data)
{
	char	*additional_input;

	signals_interactive();
	additional_input = readline("Enter command:\n >");
	signals_noninteractive();
	if (!additional_input)
	{
		write(STDERR_FILENO, "Syntax error: unexpected end of file\n", 38);
		exit_minishell(data, 2);
	}
	if (additional_input && *additional_input) 
	{
		data->input = append_input(data->input, additional_input);
		if (!data->input)
			return (false);
	}
	free(additional_input);
	return (true);
}

bool	return_ctrld(t_cmd *cmd)
{
	printf("Warning: here-document recieved EOF (wanted `%s')\n",
		cmd->heredoc_delimiter);
	return (true);
}

bool	process_h_input(t_cmd *cmd)
{
	char	*addin;
	char	*new_input;

	while (cmd->heredoc)
	{
		signals_interactive();
		addin = readline("Enter input:\n> ");
		signals_noninteractive();
		if (!addin)
			return (return_ctrld(cmd));
		if (strcmp(addin, cmd->heredoc_delimiter) == 0)
		{
			cmd->heredoc = false;
			free(addin);
			return (true);
		}
		new_input = append_input(cmd->h_input, addin);
		free(addin);
		if (!new_input)
			return (false);
		cmd->h_input = new_input;
	}
	return (false);
}
