/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution_Utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 07:18:50 by razamora          #+#    #+#             */
/*   Updated: 2024/09/07 21:18:55 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

char	*ft_get_path(char **full_cmd, char **envp)
{
	char	*cmd;
	char	*path;
	char	**path_split;
	int		i;
	char	*new;

	i = 0;
	path = ft_find_path(envp);
	if (path == NULL)
	{
		new = ft_strdup(full_cmd[0]);
		(ft_command_error(new, envp));
	}
	cmd = ft_strjoin("/", full_cmd[0]);
	path_split = ft_split(path, ':');
	while (path_split[i] != NULL)
	{
		path = ft_strjoin(path_split[i], cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (free(cmd), ft_freedbl(path_split), path);
		free(path);
		i++;
	}
	(free(cmd), ft_freedbl(path_split));
	return (NULL);
}

int static	is_builtin(char **s_cmd, char **ev)
{
	t_env	*create;
	int		code;

	create = create_env_variables(ev, 0, NULL);
	code = exec_builtin(s_cmd, create, ev, NULL);
	free_env(create);
	ft_freedbl(s_cmd);
	return (code);
}

void	execute_command(char **s_cmd, char **ev)
{
	char	*path;

	if (s_cmd == NULL || s_cmd[0] == NULL)
		exit(1);
	if (builtin(s_cmd[0]))
		exit(is_builtin(s_cmd, ev));
	if (access(s_cmd[0], F_OK | X_OK) == 0 && s_cmd[0][0] == '/')
	{
		if (execve(s_cmd[0], s_cmd, ev) == -1)
			ft_command_error(s_cmd[0], ev);
	}
	if (access(s_cmd[0], F_OK | X_OK) == 0 && ft_strnstr(s_cmd[0], "./", 2))
	{
		if (execve(s_cmd[0], s_cmd, ev) == -1)
			ft_command_error(s_cmd[0], ev);
	}
	else if (access(s_cmd[0], F_OK | X_OK) != 0 && ft_strchr(s_cmd[0], '/'))
		ft_command_error(s_cmd[0], ev);
	else
	{
		path = ft_get_path(s_cmd, ev);
		if (path == NULL || execve(path, s_cmd, ev) == -1)
			ft_command_error(s_cmd[0], ev);
		free(path);
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_error_file(int *file_pipe, char *file)
{
	close(file_pipe[0]);
	close(file_pipe[1]);
	perror(file);
}
