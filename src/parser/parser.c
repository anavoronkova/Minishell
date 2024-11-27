/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:33:41 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/26 18:38:24 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_token(t_data *data, t_cmd *command, t_token **current, int *ac)
{
	t_token	*token;

	token = *current;
	if (token->type == ENV || token->value[0] == '~')
		handle_env(data, command, ac, token);
	else if (token->type == WORD)
		decide_if_join(command, token, token->value, ac);
	else if (token->type == REDIR_IN || token->type == HEREDOC)
	{
		if (handle_input_redirect(data, command, current))
			return (nferr);
	}
	else if (token->type == REDIR_OUT || token->type == APPEND)
	{
		if (handle_output_redirect(data, command, current))
			return (nferr);
	}
	else if (token->type == QUOTE || token->type == DOUBLEQUOTE)
		handle_quotes(data, command, current, ac);
	if (token == *current)
		*current = (*current)->next;
	return (success);
}

int	single_cmd(t_data *data, t_cmd *cmd, t_token *tokens, t_token **last_token)
{
	int		ac;

	ac = 0;
	if (!check_tokens(cmd, tokens))
		return (nferr);
	if (initialize_output_array(cmd) || initialize_input_array(cmd))
		return (ferr);
	while (tokens)
	{
		if (tokens && tokens->type == PIPE)
		{
			*last_token = tokens;
			break ;
		}
		if (handle_token(data, cmd, &tokens, &ac))
			return (nferr);
		if (cmd->args[ac])
			ac++;
	}
	if (!(*last_token) && tokens)
		*last_token = tokens;
	return (success);
}

int	parsing_loop(t_data *data, t_cmd **first_cmd,
		t_token **tokens, t_token **last_tkn)
{
	t_cmd	*current_command;
	int		result;

	current_command = *first_cmd;
	while (*tokens)
	{
		result = single_cmd(data, current_command, *tokens, last_tkn);
		if (result)
			return (result);
		if (*last_tkn && (*last_tkn)->type == PIPE)
		{
			*tokens = *last_tkn;
			if (!is_valid_after_pipe(tokens, current_command))
				return (nferr);
			*last_tkn = NULL;
			if (current_command->pipe == true)
				return (epipe);
			if (new_command(&current_command))
				return (ferr);
		}
		else
			break ;
	}
	return (success);
}

int	parser(t_data *data)
{
	t_cmd		*first_command;
	t_token		*last_token;
	t_token		*tokens;
	int			result;

	last_token = NULL;
	first_command = NULL;
	if (!data->tokens)
		return (success);
	tokens = data->tokens;
	first_command = initialize_parsing();
	if (!first_command)
		return (ferr);
	result = parsing_loop(data, &first_command, &tokens, &last_token);
	data->commands = first_command;
	if (result == epipe)
	{
		if (handle_empty_pipe(data))
			return (epipe);
		else
			return (success);
	}
	if (result)
		return (result);
	return (success);
}
