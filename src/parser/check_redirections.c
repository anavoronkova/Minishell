/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:28:37 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/26 18:19:46 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	has_valid_filename_after_redirection(t_token *current_token)
{
	current_token = current_token->next;
	while (current_token != NULL
		&& (current_token->type == TOKEN_SPACE
			|| current_token->type == TOKEN_TAB))
		current_token = current_token->next;
	if (current_token == NULL)
	{
		printf("Redirection without a filename\n");
		return (false);
	}
	return (true);
}

bool	check_input_redir(t_token **current_token, t_cmd *command)
{
	command->input_counter++;
	if (!has_valid_filename_after_redirection(*current_token))
		return (false);
	*current_token = (*current_token)->next;
	while (*current_token != NULL
		&& ((*current_token)->type == TOKEN_SPACE
			|| (*current_token)->type == TOKEN_TAB))
		*current_token = (*current_token)->next;
	return (true);
}

bool	check_output_redir(t_token **current_token, t_cmd *command)
{
	command->output_counter++;
	if (!has_valid_filename_after_redirection(*current_token))
		return (false);
	*current_token = (*current_token)->next;
	while (*current_token != NULL
		&& ((*current_token)->type == TOKEN_SPACE
			|| (*current_token)->type == TOKEN_TAB))
		*current_token = (*current_token)->next;
	return (true);
}

bool	validate_redirection_syntax(t_token *tokens, t_cmd *command)
{
	if (tokens->type == REDIR_IN)
	{
		if (!check_input_redir(&tokens, command))
			return (false);
	}
	if (tokens->type == REDIR_OUT || tokens->type == APPEND)
	{
		if (!check_output_redir(&tokens, command))
			return (false);
	}
	return (true);
}
