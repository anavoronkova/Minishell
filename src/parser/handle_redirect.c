/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:29:46 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/26 18:42:25 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_ofilename(t_data *data, t_cmd **command, t_token **next)
{
	char	*temp;

	temp = NULL;
	if ((*next)->type == QUOTE)
	{
		*next = (*next)->next;
		temp = handle_single_quote(next);
		(*command)->output[(*command)->output_counter] = ft_strdup(temp);
		free(temp);
	}
	else if ((*next)->type == DOUBLEQUOTE)
	{
		*next = (*next)->next;
		temp = handle_double_quote(data, next);
		(*command)->output[(*command)->output_counter] = ft_strdup(temp);
		free(temp);
	}
	else if ((*next)->value[0] == '$')
		return (handle_error((*next)->value, "ambiguous redirect", nferr));
	else
		(*command)->output[(*command)->output_counter]
			= ft_strdup((*next)->value);
	return (success);
}

int	get_ifilename(t_data *data, t_cmd **command, t_token **next)
{
	char	*temp;

	temp = NULL;
	if ((*next)->type == QUOTE)
	{
		*next = (*next)->next;
		temp = handle_single_quote(next);
		(*command)->input[(*command)->input_counter] = ft_strdup(temp);
		free(temp);
	}
	else if ((*next)->type == DOUBLEQUOTE)
	{
		*next = (*next)->next;
		temp = handle_double_quote(data, next);
		(*command)->input[(*command)->input_counter] = ft_strdup(temp);
		free(temp);
	}
	else if ((*next)->value[0] == '$')
		return (handle_error((*next)->value, "ambiguous redirect", nferr));
	else
		(*command)->input[(*command)->input_counter]
			= ft_strdup((*next)->value);
	return (success);
}

char	*handle_heredoc(t_cmd *command, t_token **current)
{
	char	*delimiter;
	char	*input_string;

	delimiter = (*current)->value;
	input_string = ft_strdup("");
	if (!input_string)
	{
		perror("Memory allocation error in handle_heredoc\n");
		return (NULL);
	}
	command->heredoc_delimiter = ft_strdup(delimiter);
	*current = (*current)->next;
	command->heredoc = true;
	return (input_string);
}

int	handle_input_redirect(t_data *data, t_cmd *command, t_token **current)
{
	t_token	*next;

	next = (*current)->next;
	while (next && (next->type == TOKEN_SPACE || next->type == TOKEN_TAB))
		next = next->next;
	if (next != NULL)
	{
		if ((*current)->type == HEREDOC)
			command->h_input = handle_heredoc(command, &next);
		else if (get_ifilename(data, &command, &next) == nferr)
			return (nferr);
		if (!command->heredoc)
			command->input_counter++;
		if (next)
			*current = next->next;
		else
			*current = next;
		return (success);
	}
	else
		return (handle_error(command->args[0],
				"expected a filename of heredoc delimiter", nferr));
}

int	handle_output_redirect(t_data *data, t_cmd *command, t_token **current)
{
	t_token	*next_token;

	next_token = (*current)->next;
	while (next_token != NULL
		&& (next_token->type == TOKEN_SPACE || next_token->type == TOKEN_TAB))
		next_token = next_token->next;
	if (next_token != NULL)
	{
		if (get_ofilename(data, &command, &next_token) == nferr)
			return (nferr);
		command->output_counter++;
		if ((*current)->type == APPEND)
			command->append = 1;
		if (next_token)
			*current = next_token->next;
		else
			*current = next_token;
		return (success);
	}
	else
		return (handle_error(command->args[0], "expected a filename", nferr));
}
