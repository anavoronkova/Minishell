/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:14:26 by boiarinov         #+#    #+#             */
/*   Updated: 2024/04/20 17:45:09 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_not_word(char symbol)
{
	return (symbol == '\t' || symbol == ' ' || symbol == '\"'
		|| symbol == '\'' || symbol == '|' || symbol == '>'
		|| symbol == '<' || symbol == '\n');
}

int	create_word_token(t_ls *ls, int start, int *i)
{
	char	*substr;

	substr = NULL;
	substr = ft_substr(ls->data->input, start, *i - start);
	if (!substr)
	{
		perror("Error: failed to create a word token name\n");
		return (nferr);
	}
	if (token_init(ls, WORD, substr))
	{
		free(substr);
		return (nferr);
	}
	free(substr);
	return (success);
}

int	process_words(t_ls *ls, int *i)
{
	int		start;

	start = *i;
	while (ls->data->input[*i] && !is_not_word(ls->data->input[*i]))
	{
		if (ls->data->input[*i] == '$'
			&& (ft_isalnum(ls->data->input[*i + 1])
				|| ls->data->input[*i + 1] == '?'))
		{
			if (*i > start)
			{
				if (create_word_token(ls, start, i))
					return (nferr);
			}
			return (process_env(ls, i));
		}
		(*i)++;
	}
	if (*i > start)
	{
		if (create_word_token(ls, start, i))
			return (nferr);
	}
	return (success);
}

int	lexer_loop(t_ls *ls)
{
	int	i;

	i = 0;
	while (ls->data->input[i])
	{
		if (!is_not_word(ls->data->input[i]))
		{
			if (process_words(ls, &i))
			{
				perror("Error: failed to create a word token\n");
				return (nferr);
			}
		}
		if (is_not_word(ls->data->input[i]))
		{
			if (!process_non_words(ls, &i))
			{
				perror("Error: failed to create a non-word token\n");
				return (nferr);
			}
		}
	}
	return (success);
}

int	lexer(t_data *data)
{
	t_token	*current;
	t_token	*last;
	t_ls	*lexer_state;

	last = NULL;
	lexer_state = init_lexer_state(data);
	if (!lexer_state)
		return (ferr);
	current = data->tokens;
	while (current)
	{
		last = current;
		current = current->next;
	}
	lexer_state->current = last;
	if (lexer_loop(lexer_state))
	{
		free(lexer_state);
		return (ferr);
	}
	data->tokens = lexer_state->first;
	free(lexer_state);
	return (success);
}
