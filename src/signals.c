/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:39:47 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/24 13:57:20 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_line(int signum)
{
	(void)signum;
	g_signal_received = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	display_new_line(int signum)
{
	if (signum == SIGQUIT)
	{
		g_signal_received = 131;
		printf("Quit (core dumped)\n");
	}
	else
	{
		g_signal_received = 130;
		write(1, "\n", 1);
	}
	rl_on_new_line();
}

/*void	rl_quit(int signum)
{
	if (signum == SIGINT)
		rl_replace_line("", 0);
}

void	signals_addin(void)
{
	signal(SIGINT, rl_quit);
	signal(SIGQUIT, SIG_IGN);
}*/

void	signals_interactive(void)
{
	signal(SIGINT, reset_line);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_noninteractive(void)
{
	signal(SIGINT, display_new_line);
	signal(SIGQUIT, display_new_line);
}
