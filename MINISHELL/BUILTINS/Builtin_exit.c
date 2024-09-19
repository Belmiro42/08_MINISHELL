/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:05:45 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

static int	get_num(char *str, t_env *environment)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (index == 0 && (str[index] == '-' || str[index] == '+'))
			index++;
		if (!str[index] || !ft_isdigit(str[index]))
		{
			ft_putstr_fd("Minishekk: exit: numeric argument required\n", 2);
			return (2);
		}
	}
	free(environment->value);
	environment->value = ft_strdup(str);
	index = ft_atoi(str);
	return (index);
}

int	exit_builtin(char **args, t_env *environment, t_set *set)
{
	int	exit_code;

	(void)set;
	exit_code = ft_atoi(environment->value);
	if (args)
	{
		if (ft_arrlen(args) > 1)
		{
			if (ft_arrlen(args) > 2)
			{
				ft_putstr_fd("Minishekk: exit: too many arguments", 2);
				exit_code = 1;
				return (free_env(environment), exit(exit_code), 0);
			}
			exit_code = get_num(args[1], environment);
		}
	}
	free_env(environment);
	ft_putstr_fd("exit\n", 1);
	exit(exit_code);
}
