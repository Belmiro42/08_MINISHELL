/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:53:30 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │								HEREDOC									│
//  └───────────────────────────────────────────────────────────────────────┘

static void	heredoc_prompt(char *limiter, int *count)
{
	int	i;

	i = -1;
	write(1, "Delimiter: ", 11);
	while (++i < 14)
	{
		if (limiter[i] != '\n')
			write(1, &limiter[i], 1);
		else
			while (++i < 15)
				write(1, " ", 1);
		if (i == 9)
		{
			while (++i < 13)
				write(1, ".", 1);
			write(1, " ", 1);
		}
	}
	write(1, "heredoc>", 9);
	(*count)++;
}

char	*fn(t_input *heredoc, t_env *env, int fd, char **limiter)
{
	char	*input_line;
	int		count;

	count = 0;
	while (true)
	{
		heredoc_prompt(*limiter, &count);
		input_line = get_next_line(0);
		if (input_line && ft_strcmp(*limiter, input_line) != 0)
		{
			if (!heredoc->expand)
				input_line = variable_expansion_hd(input_line, env);
			write(fd, input_line, ft_strlen(input_line));
			free(input_line);
		}
		else
		{
			if (!input_line && !g_signal_triggered)
				msm_heredoc(heredoc->filename, count);
			return (free(*limiter), close(fd), free(input_line), heredoc->tmp);
		}
	}
}

char	*heredoc(t_input *heredoc, t_env *env, t_set *set)
{
	int		fd;
	char	*limiter;

	limiter = add_character('\n', heredoc->filename, KEEP);
	if (!limiter)
	{
		free_parser_struct(set);
		free_env(env);
		exit(4);
	}
	fd = open(heredoc->tmp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (free(limiter), (void)(limiter = NULL),
			unlink(heredoc->tmp), NULL);
	if (!g_signal_triggered)
		return (fn(heredoc, env, fd, &limiter));
	return (NULL);
}

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │								REDIRECTION								│
//  └───────────────────────────────────────────────────────────────────────┘

void	handle_heredoc(t_pipe *pipe, t_env *env, t_set *set)
{
	t_input	*in;

	while (pipe)
	{
		in = pipe->in;
		while (in && !g_signal_triggered)
		{
			if (in->heredoc == 1)
				heredoc(in, env, set);
			in = in->next;
		}
		pipe = pipe->next;
	}
}
