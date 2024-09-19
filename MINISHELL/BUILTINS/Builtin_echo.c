/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:25:35 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

bool	is_flag(char *str)
{
	if (str && (!(str[0] == '-' && str[1] == 'n')))
		return (false);
	while (*(++str))
		if (!(*str == 'n'))
			return (false);
	return (true);
}

void	find_all_flags(char **args, int *iterator, bool *flag)
{
	while (args[++(*iterator)] && is_flag(args[*iterator]))
		*flag = true;
}

static void	print_to_std(char **args, int iterator, bool flag, int start)
{
	while (args[iterator])
	{
		if (start++ > 0)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(args[iterator++], 1);
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
}

int	echo_builtin(char **args, t_env *environment)
{
	bool	flag;
	int		iterator;

	(void)environment;
	flag = 0;
	iterator = 0;
	find_all_flags(args, &iterator, &flag);
	print_to_std(args, iterator, flag, 0);
	return (EXIT_SUCCESS);
}
