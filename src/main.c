/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:08:10 by aboiarin          #+#    #+#             */
/*   Updated: 2024/04/29 18:10:31 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile int	g_signal_received;

int	main_loop(t_data *data)
{
	int			parser_status;
	int			lexer_status;
	int			executor_status;

	lexer_status = lexer(data);
	if (lexer_status != success)
		return (handle_error(NULL, "Lexer error. Exiting\n", ferr));
	parser_status = parser(data);
	if (parser_status == nferr)
	{
		data->exit_status = 2;
		return (handle_error(NULL, NULL, nferr));
	}
	else if (parser_status == ferr)
		return (handle_error(NULL, "Fatal parser error\n", ferr));
	else if (parser_status == epipe)
		return (epipe);
	executor_status = executor(data->commands, data);
	if (executor_status == nferr)
		return (handle_error(NULL, NULL, nferr));
	else if (executor_status == ferr)
		return (handle_error(NULL, "Fatal executor error\n", ferr));
	return (success);
}

void	run_minishell(t_data *data)
{
	int		main_loop_status;

	while (1)
	{
		data->prompt = get_prompt();
		signals_interactive();
		data->input = readline(data->prompt);
		if (!data->input)
			exit_minishell(data, EXIT_SUCCESS);
		set_exit_status(data, 0, 0);
		signals_noninteractive();
		if (data->input)
			add_history(data->input);
		main_loop_status = main_loop(data);
		if (main_loop_status == ferr)
			exit_minishell(data, EXIT_FAILURE);
		while (main_loop_status == epipe)
		{
			free_data(data, 2);
			main_loop_status = main_loop(data);
		}
		free_data(data, 0);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	g_signal_received = 0;
	ft_memset(&data, 0, sizeof(t_data));
	if (init_data_env(&data) != success)
		handle_error(NULL, "Failed to allocate data.env\n", nferr);
	if (argc != 1)
	{
		errno = EINVAL;
		printf("This program does not accept arguments\n");
		exit(EXIT_FAILURE);
	}
	disable_echoctl();
	run_minishell(&data);
	exit_minishell(&data, data.exit_status);
}

void	exit_minishell(t_data *data, int exit_code)
{
	printf("Exiting minishell...\n");
	if (getenv("HISTFILE="))
		write_history(getenv("HISTFILE=") + 9);
	enable_echoctl();
	free_data(data, 1);
	rl_clear_history();
	exit(exit_code);
}
