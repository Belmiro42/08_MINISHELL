/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:02:21 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

// DESCRIPTION: SYNOPSIS
// env [OPTION]... [-] [NAME=VALUE]... [COMMAND [ARG]...]
// For minishekk we want no arguments.
int	env_builtin(char **args, t_env *environment)
{
	t_env	*cpy;

	cpy = environment;
	if (ft_arrlen(args) > 2)
	{
		ft_putstr_fd("Minishekk: env: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	environment = environment->next;
	while (environment)
	{
		ft_putstr_fd(environment->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(environment->value, 1);
		ft_putstr_fd("\n", 1);
		environment = environment->next;
	}
	return (EXIT_SUCCESS);
}
