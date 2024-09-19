/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution_Utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 07:22:03 by razamora          #+#    #+#             */
/*   Updated: 2024/09/14 13:54:05 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

void static	error(char *cmd, char *msm, int code_error)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msm, 2);
	exit(code_error);
}

void static	file_error(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '.' && !ft_strchr(cmd, '/'))
		return ;
	if (access(cmd, F_OK) != 0 && ft_strchr(cmd, '/'))
		error(cmd, ": No such file or directory\n", 127);
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
	{
		if (access(cmd, X_OK) != 0)
			error(cmd, ": Permission denied\n", 126);
		else if (access(cmd, F_OK) == 0 && ((cmd[0] == '.' && cmd[1] == '.') \
		|| ft_strchr(cmd, '/')))
			error(cmd, ": Is a directory\n", 126);
	}
	if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		error(cmd, ": Is a directory\n", 126);
	else if (cmd[0] == '.' && cmd[1] == '\0')
	{
		write(2, "filename argument required\n", 27);
		exit(2);
	}
}

int	ft_command_error(char *cmd, char **envp)
{
	char	*argva[3];

	argva[0] = "command-not-found";
	argva[1] = cmd;
	argva[2] = NULL;
	file_error(cmd);
	execve("/usr/lib/command-not-found", argva, envp);
	cmd = ft_strjoin(cmd, "\n");
	write(2, "command not found: ", 19);
	write(2, cmd, ft_strlen(cmd));
	free(cmd);
	exit(127);
}

int	catch_exit_code(int argc, pid_t *pids)
{
	int	status;
	int	error;
	int	i;

	error = 0;
	i = 0;
	while (argc > i)
		waitpid(pids[i++], &status, 0);
	waitpid(pids[i], &status, 0);
	error = (WEXITSTATUS(status));
	free(pids);
	return (error);
}

void	is_shellception(char **args)
{
	char	*cmd;

	if (args)
	{
		if (args[0])
		{
			cmd = ft_strnstr(args[0], "/minishell", ft_strlen(args[0]));
			if (cmd)
				shellception();
		}
	}
}
