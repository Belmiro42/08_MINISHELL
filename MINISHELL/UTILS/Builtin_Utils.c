/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin_Utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:06:16 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/08 12:47:39 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

bool	builtin(char *str)
{
	if (!str)
		return (false);
	if (ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "unset") == 0)
		return (true);
	return (false);
}

int	exec_builtin(char **args, t_env *env, char **envp, t_set *set)
{
	if (envp)
		ft_freedbl(envp);
	if (ft_strcmp(args[0], "cd") == 0)
		return (cd_builtin(args, env));
	if (ft_strcmp(args[0], "echo") == 0)
		return (echo_builtin(args, env));
	if (ft_strcmp(args[0], "env") == 0)
		return (env_builtin(args, env));
	if (ft_strcmp(args[0], "exit") == 0)
		exit_builtin(args, env, set);
	if (ft_strcmp(args[0], "export") == 0)
		return (export_builtin(args, env));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd_builtin(args, env));
	if (ft_strcmp(args[0], "unset") == 0)
		return (unset_builtin(args, env));
	return (69);
}
