/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal_Handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:50:52 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/11 18:12:34 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

static void	default_handler(int sigval)
{
	if (sigval == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal_triggered = SIGINT;
	}
}

static void	infunc(int sigval)
{
	write(1, "\n", 1);
	g_signal_triggered = sigval;
}

void	default_signals(void)
{
	struct sigaction	new_line;
	struct sigaction	ignore;

	sigemptyset(&new_line.sa_mask);
	ft_memset(&new_line, 0, sizeof(new_line));
	new_line.sa_handler = &default_handler;
	new_line.sa_flags = 0;
	sigaction(SIGINT, &new_line, NULL);
	ft_memset(&ignore, 0, sizeof(ignore));
	sigemptyset(&ignore.sa_mask);
	ignore.sa_handler = SIG_IGN;
	ignore.sa_flags = 0;
	sigaction(SIGQUIT, &ignore, NULL);
}

void	infunc_signals(void)
{
	struct sigaction	exit_func;

	sigemptyset(&exit_func.sa_mask);
	ft_memset(&exit_func, 0, sizeof(exit_func));
	exit_func.sa_handler = &infunc;
	exit_func.sa_flags = 0;
	sigaction(SIGINT, &exit_func, NULL);
	sigaction(SIGQUIT, &exit_func, NULL);
}

void	shellception(void)
{
	struct sigaction	ignore;

	ft_memset(&ignore, 0, sizeof(ignore));
	sigemptyset(&ignore.sa_mask);
	ignore.sa_handler = SIG_IGN;
	ignore.sa_flags = 0;
	sigaction(SIGQUIT, &ignore, NULL);
	sigaction(SIGINT, &ignore, NULL);
}
