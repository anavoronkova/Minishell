/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:29:34 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/22 11:07:48 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ls	*init_lexer_state(t_data *data)
{
	t_ls	*temp;

	temp = malloc(sizeof(t_ls));
	if (!temp)
	{
		write(STDERR_FILENO, "Memory allocation failed for lexer_state\n", 42);
		return (NULL);
	}
	temp->data = data;
	temp->current = data->tokens;
	temp->first = data->tokens;
	return (temp);
}

int	token_init(t_ls *ls, t_token_type type, const char *value)
{
	t_token	*token_new;
	char	*dup;

	token_new = malloc(sizeof(t_token));
	if (!token_new)
		return (nferr);
	dup = ft_strdup(value);
	if (!dup)
	{
		free(token_new);
		return (handle_error(value, "failed to set token value", nferr));
	}
	token_new->type = type;
	token_new->value = dup;
	token_new->next = NULL;
	token_new->previous = ls->current;
	if (!ls->first)
		ls->first = token_new;
	else if (ls->current)
		ls->current->next = token_new;
	ls->current = token_new;
	return (success);
}
