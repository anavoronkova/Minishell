/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:43:37 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/29 15:21:18 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*add_quoted_string(t_token **token, char **quoted_string)
{
	char	*temp;

	temp = NULL;
	if (*quoted_string == NULL)
		*quoted_string = ft_strdup((*token)->value);
	else
	{
		temp = ft_strjoin(*quoted_string, (*token)->value);
		free(*quoted_string);
		*quoted_string = temp;
	}
	if (!*quoted_string)
		return (NULL);
	return (*quoted_string);
}

char	*handle_double_quote(t_data *data, t_token **token)
{
	char	*quoted_string;
	char	*temp;

	quoted_string = ft_strdup("");
	temp = NULL;
	while (*token && (*token)->type != DOUBLEQUOTE)
	{
		if ((*token)->type == ENV)
			temp = handle_quoted_env(data, *token, &quoted_string);
		else
			temp = add_quoted_string(token, &quoted_string);
		if (temp)
			quoted_string = temp;
		*token = (*token)->next;
	}
	if (*token && (*token)->type == DOUBLEQUOTE)
		*token = (*token)->next;
	return (quoted_string);
}

char	*handle_single_quote(t_token **token)
{
	char	*quoted_string;
	char	*temp;

	quoted_string = ft_strdup("");
	temp = NULL;
	while (*token && (*token)->type != QUOTE)
	{
		temp = add_quoted_string(token, &quoted_string);
		quoted_string = temp;
		*token = (*token)->next;
	}
	if (*token && (*token)->type == QUOTE)
		*token = (*token)->next;
	return (quoted_string);
}

void	handle_quotes(t_data *data, t_cmd *command, t_token **current, int *ac)
{
	t_token	*token;
	char	*quoted_string;

	token = *current;
	quoted_string = NULL;
	if (token->type == QUOTE)
	{
		token = token->next;
		quoted_string = handle_single_quote(&token);
	}
	else if (token->type == DOUBLEQUOTE)
	{
		token = token->next;
		quoted_string = handle_double_quote(data, &token);
	}
	if (*ac > 0 && command->args[*ac - 1])
		decide_if_join(command, *current, quoted_string, ac);
	else
	{
		command->args[*ac] = ft_strdup(quoted_string);
		(*ac)++;
	}
	free(quoted_string);
	*current = token;
}
