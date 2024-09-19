/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:05:16 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/07 14:32:31 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

int	gotodir(t_env *environment, char *path)
{
	char	*new_path;
	char	*cwd;

	cwd = NULL;
	new_path = path;
	if (!access(new_path, R_OK | F_OK))
	{
		cwd = getcwd(cwd, 0);
		new_val_env("OLDPWD", cwd, &environment);
		free(cwd);
		cwd = NULL;
		chdir(new_path);
		cwd = getcwd(cwd, 0);
		new_val_env("PWD", cwd, &environment);
		free(cwd);
		return (EXIT_SUCCESS);
	}
	perror("Minishekk: cd");
	return (EXIT_FAILURE);
}

static int	prv_dir(t_env *environment)
{
	char	*prev_path;
	char	*cwd;

	cwd = NULL;
	prev_path = get_val_env("OLDPWD", environment);
	if (!prev_path)
		ft_putstr_fd("Minishekk: cd: OLDPWD not set\n", 2);
	if (!prev_path)
		return (free(prev_path), EXIT_FAILURE);
	if (!access(prev_path, R_OK | F_OK))
	{
		cwd = getcwd(cwd, 0);
		new_val_env("OLDPWD", cwd, &environment);
		free(cwd);
		cwd = NULL;
		chdir(prev_path);
		cwd = getcwd(cwd, 0);
		new_val_env("PWD", cwd, &environment);
		free(cwd);
		free(prev_path);
		pwd_builtin(NULL, environment);
		return (EXIT_SUCCESS);
	}
	perror("Minishekk: cd");
	return (free(prev_path), EXIT_FAILURE);
}

static int	no_args(t_env *environment)
{
	char	*home_path;
	char	*cwd;

	cwd = NULL;
	home_path = get_val_env("HOME", environment);
	if (!home_path)
		ft_putstr_fd("Minishekk: cd: HOME not set\n", 2);
	if (!home_path)
		return (free(home_path), EXIT_FAILURE);
	if (!access(home_path, R_OK | F_OK))
	{
		cwd = getcwd(cwd, 0);
		new_val_env("OLDPWD", cwd, &environment);
		free(cwd);
		cwd = NULL;
		chdir(home_path);
		cwd = getcwd(cwd, 0);
		new_val_env("PWD", cwd, &environment);
		free(cwd);
		free(home_path);
		return (EXIT_SUCCESS);
	}
	perror("Minishekk: cd");
	return (free(home_path), EXIT_FAILURE);
}

static void	checkdir(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
	{
		chdir("/");
		pwd = NULL;
		pwd = getcwd(pwd, 0);
	}
	free(pwd);
}

int	cd_builtin(char **args, t_env *environment)
{
	checkdir();
	if (ft_arrlen(args) > 2)
	{
		ft_putstr_fd("Minishekk: cd: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (ft_arrlen(args) == 1)
	{
		if (!no_args(environment))
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	if (args[1][0] == '-' && !args[1][1])
	{
		if (!prv_dir(environment))
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	else
	{
		if (!gotodir(environment, args[1]))
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
}
