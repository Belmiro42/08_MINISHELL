/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Single_Exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:52:41 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/11 13:59:26 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │								SINGLE EXEC								│
//  └───────────────────────────────────────────────────────────────────────┘

int static	without_cmd(t_set *set)
{
	int		status;
	pid_t	pid;
	int		fd[2];

	if (!g_signal_triggered)
	{
		pid = fork();
		if (pid == 0)
		{
			fd[0] = handle_infile(set->pipe->in);
			if (fd[0] < 0)
				exit(1);
			fd[1] = handle_outfile(set->pipe->out);
			if (fd[1] < 0)
				exit(1);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, &status, 0);
		return ((WEXITSTATUS(status)));
	}
	return (130);
}

int static	pre_build(t_set *set, t_env *env, char **args)
{
	int	status;
	int	fd[2];
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	fd[0] = handle_infile(set->pipe->in);
	if (fd[0] < 0)
		return (1);
	fd[1] = handle_outfile(set->pipe->out);
	if (fd[1] < 0)
		return (1);
	status = exec_builtin(args, env, NULL, set);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	return (status);
}

int static	internal_process(t_set *set, t_env *env)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pid = fork();
	if (pid == 0)
	{
		fd[0] = handle_infile(set->pipe->in);
		if (fd[0] < 0)
			exit(1);
		fd[1] = handle_outfile(set->pipe->out);
		if (fd[1] < 0)
			exit(1);
		bash();
		if (set->pipe->args[0])
			execute_command(set->pipe->args, env_to_char(env));
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	return ((WEXITSTATUS(status)));
}

int	one_exec(t_set *set, t_env *env)
{
	t_pipe	*cpy;

	cpy = set->pipe;
	infunc_signals();
	is_shellception(cpy->args);
	handle_heredoc(set->pipe, env, set);
	if (!set->pipe->args)
		return (without_cmd(set));
	if (!builtin(set->pipe->args[0]) && !g_signal_triggered)
		return (internal_process(set, env));
	else if (!g_signal_triggered)
		return (pre_build(set, env, set->pipe->args));
	return (130);
}
