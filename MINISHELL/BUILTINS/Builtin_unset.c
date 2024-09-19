/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:04:08 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

int	unset_builtin(char **arg, t_env *env)
{
	int	iterator;
	int	exit_code;

	iterator = 0;
	exit_code = EXIT_SUCCESS;
	while (arg[++iterator])
	{
		if (ft_strnstr(arg[iterator], "=", ft_strlen(arg[iterator])))
			exit_code = EXIT_FAILURE;
		else
			del_var_env(arg[iterator], &env);
	}
	return (exit_code);
}
