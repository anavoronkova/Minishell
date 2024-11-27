/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:27:59 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/28 14:04:00 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	toggle_quote_states(t_token *tokens, bool *quote, bool *double_quote)
{
	t_token	*current_token;

	current_token = tokens;
	while (current_token)
	{
		if (current_token->type == QUOTE)
		{
			if (!(*double_quote))
				*quote = !(*quote);
		}
		else if (current_token->type == DOUBLEQUOTE)
		{
			if (!(*quote))
				*double_quote = !(*double_quote);
		}
		current_token = current_token->next;
	}
}

bool	are_quotes_closed(t_token *tokens)
{
	bool	in_single_quote;
	bool	in_double_quote;

	in_single_quote = false;
	in_double_quote = false;
	toggle_quote_states(tokens, &in_single_quote, &in_double_quote);
	if (in_single_quote || in_double_quote)
	{
		write(STDERR_FILENO, "Unclosed quote detected\n", 25);
		return (false);
	}
	return (true);
}

bool	is_valid_after_pipe(t_token **token, t_cmd *current_command)
{
	t_token	*temp;

	temp = *token;
	if (temp->type == PIPE)
		temp = temp->next;
	while (temp && (temp->type == TOKEN_SPACE || temp->type == TOKEN_TAB))
		temp = temp->next;
	if (temp == NULL)
	{
		current_command->pipe = true;
		return (true);
	}
	if (temp->type == PIPE)
	{
		*token = temp;
		write(STDERR_FILENO, "Invalid command structure after pipe\n", 38);
		return (false);
	}
	*token = temp;
	return (true);
}

bool	check_tokens(t_cmd *command, t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (command->is_first_token && tokens->type == PIPE)
		return (handle_error(tokens->value, "invalid first token", 0));
	while (current && current->type != PIPE)
	{
		if (!are_quotes_closed(tokens))
			return (false);
		else if (command->is_first_token)
			command->is_first_token = false;
		if (!validate_redirection_syntax(current, command))
			return (false);
		current = current->next;
	}
	return (true);
}
