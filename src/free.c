/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 21:32:19 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/26 18:26:07 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!*arr || !arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

void	free_command(t_cmd *command)
{
	int	i;

	i = 0;
	if (command == NULL)
		return ;
	while (command->args[i])
	{
		free(command->args[i]);
		i++;
	}
	if (command->input)
		free_arr(command->input);
	if (command->h_input)
		free(command->h_input);
	if (command->output)
		free_arr(command->output);
	if (command->heredoc_delimiter)
		free(command->heredoc_delimiter);
	free(command);
}

void	free_pipeline(t_cmd *command)
{
	t_cmd	*temp;

	while (command)
	{
		temp = command;
		command = command->next;
		free_command(temp);
	}
}

void	free_data(t_data *data, int flag)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->input && flag != 2)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens)
	{
		free_tokens(data->tokens);
		data->tokens = NULL;
	}
	if (data->commands)
	{
		free_pipeline(data->commands);
		data->commands = NULL;
	}
	if (data->env && flag == 1)
	{
		free_arr(data->env);
		data->env = NULL;
	}
}
