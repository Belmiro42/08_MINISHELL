/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:28:00 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

static int	export_error_check(char *str, int *exit_status)
{
	int	iter;

	iter = 0;
	if (str[iter] == '=' || str[iter] == '\0' )
	{
		*exit_status = EXIT_FAILURE;
		ft_putstr_fd("Minishekk: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	while (str[iter] != '=' && str[iter])
	{
		if ((iter == 0 && !(ft_isalpha(str[iter]) || str[iter] == '_')) || \
		!(ft_isalpha(str[iter]) || str[iter] == '_' || ft_isdigit(str[iter])))
		{
			*exit_status = EXIT_FAILURE;
			ft_putstr_fd("Minishekk: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (1);
		}
		iter++;
	}
	return (0);
}

int	export_builtin(char **arg, t_env *environment)
{
	char	*key;
	char	*value;
	int		iter;
	int		exit_status;

	iter = 0;
	exit_status = EXIT_SUCCESS;
	while (arg[++iter] && ft_arrlen(arg) > 1)
	{
		if (!export_error_check(arg[iter], &exit_status) && \
		ft_strnstr(arg[iter], "=", ft_strlen(arg[iter])))
		{
			key = ft_substr(arg[iter], 0, (int)((long)ft_strnstr(arg[iter], \
			"=", ft_strlen(arg[iter])) - (long)arg[iter]));
			value = ft_substr(ft_strnstr(arg[iter], "=", \
			ft_strlen(arg[iter])), 1, ft_strlen(ft_strnstr(arg[iter], "=", \
			ft_strlen(arg[iter])) + 1));
			new_val_env(key, value, &environment);
			free(key);
			free(value);
		}
	}
	return (exit_status);
}
