/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nonwords.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:42:26 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/22 11:06:22 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_env(t_ls *ls, int *i)
{
	int		start;
	char	*env_name;

	start = *i;
	(*i)++;
	while (ls->data->input[*i] && ft_isalnum(ls->data->input[*i]))
		(*i)++;
	if (ls->data->input[*i] == '?')
		(*i)++;
	env_name = ft_substr(ls->data->input, start, *i - start);
	if (!env_name)
		return (handle_error(NULL, "Failed to set ENV name", nferr));
	if (token_init(ls, ENV, env_name))
	{
		free(env_name);
		return (handle_error(NULL, "Failed to create ENV token", nferr));
	}
	free(env_name);
	return (success);
}

int	process_redirection(t_ls *ls, int *i)
{
	if (ls->data->input[*i] == '>')
	{
		if (ls->data->input[*i + 1] == '>')
		{
			(*i)++;
			return (token_init(ls, APPEND, ">>"));
		}
		else
			return (token_init(ls, REDIR_OUT, ">"));
	}
	else if (ls->data->input[*i] == '<')
	{
		if (ls->data->input[*i + 1] == '<')
		{
			(*i)++;
			return (token_init(ls, HEREDOC, "<<"));
		}
		else
			return (token_init(ls, REDIR_IN, "<"));
	}
	return (handle_error(NULL, "Failed to create a redirection token", nferr));
}

bool	process_non_words(t_ls *ls, int *i)
{
	int	result;

	result = 1;
	if (ls->data->input[*i] == ' ')
		result = token_init(ls, TOKEN_SPACE, " ");
	else if (ls->data->input[*i] == '\t')
		result = token_init(ls, TOKEN_TAB, "\t");
	else if (ls->data->input[*i] == '\n')
		result = token_init(ls, TOKEN_NEWLINE, "\n");
	else if (ls->data->input[*i] == '|')
		result = token_init(ls, PIPE, "|");
	else if (ls->data->input[*i] == '>' || (ls->data->input[*i] == '<'))
		result = process_redirection(ls, i);
	else if (ls->data->input[*i] == '\"')
		result = token_init(ls, DOUBLEQUOTE, "\"");
	else if (ls->data->input[*i] == '\'')
		result = token_init(ls, QUOTE, "\'");
	if (result)
		return (false);
	(*i)++;
	return (true);
}
