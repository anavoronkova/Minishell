/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:06:46 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/26 18:19:53 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	decide_if_join(t_cmd *command, t_token *token, char *current, int *ac)
{
	char	*temp;

	temp = NULL;
	if (token->previous && token->previous->type != TOKEN_SPACE
		&& token->previous->type != PIPE && !is_redirect_type(token->previous))
	{
		temp = ft_strjoin(command->args[*ac - 1], current);
		free(command->args[*ac - 1]);
		command->args[*ac - 1] = temp;
	}
	else
		command->args[*ac] = ft_strdup(current);
}

bool	is_redirect_type(t_token *temp_tokens)
{
	return (temp_tokens->next && (temp_tokens->type == HEREDOC 
			|| temp_tokens->type == REDIR_IN 
			|| temp_tokens->type == REDIR_OUT
			|| temp_tokens->type == APPEND));
}

int	initialize_output_array(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->output_counter > 0)
	{
		cmd->output = malloc(sizeof(char *) * (cmd->output_counter + 1));
		if (!cmd->output)
			return (handle_error(cmd->args[0],
					"memory allocation failed for output array", ferr));
		while (i < cmd->output_counter)
		{
			cmd->output[i] = NULL;
			i++;
		}
		cmd->output[i] = NULL;
	}
	cmd->output_counter = 0;
	return (success);
}

int	initialize_input_array(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->input_counter > 0)
	{
		cmd->input = malloc(sizeof(char *) * (cmd->input_counter + 1));
		if (!cmd->input)
			return (handle_error(cmd->args[0],
					"memory allocation failed for intput array", ferr));
		while (i < cmd->input_counter)
		{
			cmd->input[i] = NULL;
			i++;
		}
		cmd->input[i] = NULL;
	}
	cmd->input_counter = 0;
	return (success);
}
