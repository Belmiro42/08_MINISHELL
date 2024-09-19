/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shekk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:54:49 by razamora          #+#    #+#             */
/*   Updated: 2024/09/11 20:25:05 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

void	set_exit_val(int exit_val, t_env *environment)
{
	free(environment->value);
	environment->value = ft_itoa(exit_val % 256);
}

void	signals_exit_codes(t_env *environment)
{
	if (g_signal_triggered == SIGINT)
		set_exit_val(130, environment);
	if (g_signal_triggered == SIGQUIT)
		set_exit_val(131, environment);
}

void	print_shekk(void)
{
	printf("\
						\x1B[32m\n\
		⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n\
		⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n\
		⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀ \n\
		⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀ \n\
		⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆ \n\
		⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿ \n\
		⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀ \n\
		      \x1B[37m⠚⣦⣤⠤⠤⣤⡴⠗⠃ \x1B[32m			\n\
	.  .._..  .._.\x1B[37m⢰⣿⣿⣤⣀⡈⠃⣶⡆⠐⣶⡶⡶⠲⣦⢰⣶⡆⣰⡶⢰⣶⡆⣰⡶\x1B[32m\n\
	|\\/| | |\\ | | \x1B[37m⣉⠛⠻⠿⣿⣷⣼⣿⡷⠶⣿⣿⡗⠒⠛⢹⣿⣿⣯⡀⣿⣿⣯⡀\x1B[32m\n\
	|  |_|_| \\|_|_\x1B[37m⢿⣦⣀⣠⣿⠟⠼⠿⠇⠠⠿⠧⠻⠟⠋⠸⠿⠇⠹⣷⠸⠿⠇⠹⣷⡄\x1B[32m\n");
	printf("\
	  		Behind every shell is a \x1B[37mshekk\x1B[32m...\n\
\x1B[32m\n\n\n");
}
