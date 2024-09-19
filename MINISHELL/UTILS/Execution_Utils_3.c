/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution_Utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 07:22:03 by razamora          #+#    #+#             */
/*   Updated: 2024/09/06 02:27:20 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

int	ft_command_error(char *cmd, char **envp)
{
	char	*argva[3];

	argva[0] = "command-not-found";
	argva[1] = cmd;
	argva[2] = NULL;
	write(2, "Minishekk: ", 11);
	if (access(cmd, F_OK) == 0 && ((cmd[0] == '.' && cmd[1] == '/') \
	|| cmd[0] == '/' ))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
	{
		write(2, "Permission denied\n", 18);
		exit(127);
	}
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

int	pipe_num(t_pipe *pipe)
{
	int	count;

	count = 0;
	while (pipe)
	{
		count++;
		pipe = pipe->next;
	}
	return (count);
}

void	ft_exit_heredoc(char *line, char *tmp, int *file_pipe)
{
	free(line);
	free(tmp);
	close(file_pipe[1]);
	exit(1);
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
