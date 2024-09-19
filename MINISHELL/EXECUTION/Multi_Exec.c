/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multi_Exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:50:17 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/11 17:36:57 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │								MULTI EXEC								│
//  └───────────────────────────────────────────────────────────────────────┘

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

static pid_t	first_process(t_pipe *pipe, int *file_pipe, t_env *env)
{
	int	pid;
	int	status;
	int	fd[2];

	status = 0;
	pid = fork();
	if (pid == -1)
		(perror("Error:"), exit(1));
	if (pid == 0)
	{
		fd[0] = handle_infile(pipe->in);
		if (fd[0] < 0)
			(close(file_pipe[0]), close(file_pipe[1]), exit(1));
		fd[1] = handle_outfile(pipe->out);
		if (fd[1] < 0)
			(close(file_pipe[0]), close(file_pipe[1]), exit(1));
		if (!pipe->out)
			dup2(file_pipe[1], 1);
		close(file_pipe[0]);
		close(file_pipe[1]);
		bash();
		execute_command(pipe->args, env_to_char(env));
	}
	return (pid);
}

static pid_t	middle_processes(t_pipe **curr, int file_pipe[2], t_env *env)
{
	pid_t	pid;
	int		middle_file[2];
	int		fd[2];

	*curr = (*curr)->next;
	if (pipe(middle_file) == -1)
		return (perror("Error:"), exit(EXIT_FAILURE), pid);
	pid = fork();
	if (pid == -1)
		return (perror("Error:"), exit(EXIT_FAILURE), pid);
	else if (pid == 0)
	{
		(dup2(file_pipe[0], 0), dup2(middle_file[1], 1));
		fd[0] = handle_infile((*curr)->in);
		if (fd[0] < 0)
			exit(close_middle_fd(file_pipe, middle_file));
		fd[1] = handle_outfile((*curr)->out);
		if (fd[1] < 0)
			exit(close_middle_fd(file_pipe, middle_file));
		close_last_middle_fd(file_pipe, middle_file);
		execute_command((*curr)->args, env_to_char(env));
	}
	(close(file_pipe[0]), close(middle_file[1]));
	file_pipe[0] = middle_file[0];
	return (pid);
}

static pid_t	last_process(t_pipe *curr, int *file_pipe, t_env *env)
{
	pid_t	pid;
	int		fd[2];

	pid = fork();
	if (pid == -1)
		(perror("Error:"), exit(1));
	if (pid == 0)
	{
		dup2(file_pipe[0], 0);
		fd[0] = handle_infile(curr->in);
		if (fd[0] < 0)
			(close(file_pipe[0]), close(file_pipe[1]), exit(1));
		fd[1] = handle_outfile(curr->out);
		if (fd[1] < 0)
			(close(file_pipe[0]), close(file_pipe[1]), exit(1));
		(close(file_pipe[0]), close(file_pipe[1]));
		bash();
		execute_command(curr->args, env_to_char(env));
	}
	(close(file_pipe[0]), close(file_pipe[1]));
	return (pid);
}

int	multi_exec(t_set *set, t_env *env)
{
	int		i;
	int		file_pipe[2];
	t_pipe	*pipe_copy;
	pid_t	*pids;

	pipe_copy = set->pipe;
	pids = malloc((pipe_num(pipe_copy) + 1) * sizeof(pid_t));
	if (!pids)
		free_struct_main(set, env);
	handle_heredoc(pipe_copy, env, set);
	if (pipe(file_pipe) == -1)
		(perror("Error:"), exit(1));
	i = 0;
	if (!g_signal_triggered)
		pids[i] = first_process(pipe_copy, file_pipe, env);
	while (pipe_copy->next->next != NULL && !g_signal_triggered)
		pids[++i] = middle_processes(&pipe_copy, file_pipe, env);
	pipe_copy = pipe_copy->next;
	i++;
	if (!g_signal_triggered)
		pids[i] = last_process(pipe_copy, file_pipe, env);
	return (catch_exit_code(i, pids));
}
