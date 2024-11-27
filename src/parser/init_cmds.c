/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:24:52 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/26 18:23:25 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*initialize_command(void)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
	{
		perror("Error: memory allocation failed for command\n");
		return (NULL);
	}
	command->input = NULL;
	command->output = NULL;
	command->append = 0;
	command->output_counter = 0;
	command->input_counter = 0;
	command->heredoc = false;
	command->heredoc_delimiter = NULL;
	command->h_input = NULL;
	command->pipe = false;
	ft_bzero(command->args, sizeof(command->args));
	command->is_first_token = true;
	command->next = NULL;
	return (command);
}

int	new_command(t_cmd **current_command)
{
	(*current_command)->next = initialize_command();
	if (!((*current_command)->next))
		return (handle_error(NULL,
				"Dailed to initialize the next command in the list", ferr));
	else
		*current_command = (*current_command)->next;
	return (success);
}

t_cmd	*initialize_parsing(void)
{
	t_cmd	*first_command;

	first_command = initialize_command();
	if (!first_command)
	{
		perror("Error: failed to initialize the first command\n");
		return (NULL);
	}
	return (first_command);
}
