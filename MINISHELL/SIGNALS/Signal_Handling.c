/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal_Handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:50:52 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/09 14:07:10 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Necesario tener esto aqui sino,
#include "../MAIN/minishell.h"

static void	default_handler(int sigval)
{
	if (sigval == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	inishell(int sigval)
{
	if (sigval == SIGINT)
	{
		write(1, "\n", 1);
		g_signal_triggered = SIGINT;
	}
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
	exit_func.sa_handler = &inishell;
	exit_func.sa_flags = 0;
	sigaction(SIGINT, &exit_func, NULL);
}

void	shellception(void)
{
	struct sigaction	ignore;

	sigemptyset(&ignore.sa_mask);
	ft_memset(&ignore, 0, sizeof(ignore));
	ignore.sa_handler = SIG_IGN;
	ignore.sa_flags = 0;
	sigaction(SIGQUIT, &ignore, NULL);
	sigaction(SIGINT, &ignore, NULL);
}

void bash(void)
{
	struct sigaction bashki;

    sigemptyset(&bashki.sa_mask);
	ft_memset(&bashki, 0, sizeof(bashki));
    bashki.sa_handler = SIG_DFL;
    bashki.sa_flags = 0;
	sigaction(SIGQUIT, &bashki, NULL);
}