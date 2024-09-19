/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal_Bash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:12:06 by razamora          #+#    #+#             */
/*   Updated: 2024/09/11 18:15:15 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

void	bash(void)
{
	struct sigaction	bashki;

	sigemptyset(&bashki.sa_mask);
	ft_memset(&bashki, 0, sizeof(bashki));
	bashki.sa_handler = SIG_DFL;
	bashki.sa_flags = 0;
	sigaction(SIGQUIT, &bashki, NULL);
}
