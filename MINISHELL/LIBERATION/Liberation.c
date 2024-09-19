/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Liberation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:31:56 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

void	free_token(t_token *current)
{
	t_token	*tmp;
	t_token	*tmp_quoted;
	t_token	*tmp_real;

	while (current)
	{
		tmp = current;
		current = current->next;
		while (tmp->quoted_expanded)
		{
			tmp_quoted = tmp->quoted_expanded;
			tmp->quoted_expanded = tmp->quoted_expanded->next;
			free(tmp_quoted->token);
			free(tmp_quoted);
		}
		while (tmp->real_tokens)
		{
			tmp_real = tmp->real_tokens;
			tmp->real_tokens = tmp->real_tokens->next;
			free(tmp_real->token);
			free(tmp_real);
		}
		free(tmp->token);
		free(tmp);
	}
}

static void	free_input(t_pipe *current)
{
	t_input	*tmp;

	while (current->in)
	{
		tmp = current->in;
		current->in = current->in->next;
		free_token(tmp->token);
		if (tmp->tmp)
			free(tmp->tmp);
		free(tmp->filename);
		free(tmp);
	}
}

static void	free_output(t_pipe *current)
{
	t_output	*tmp;

	while (current->out)
	{
		tmp = current->out;
		current->out = current->out->next;
		free_token(tmp->token);
		free(tmp->filename);
		free(tmp);
	}
}

void	free_parser_struct(t_set *set)
{
	void	*tmp;
	t_pipe	*pipe;

	while ((unsigned long)set > (unsigned long)255)
	{
		pipe = set->pipe;
		while (pipe)
		{
			tmp = pipe;
			free_input(pipe);
			free_output(pipe);
			free_token(pipe->token);
			free(((t_pipe *)tmp)->args);
			if ((((t_pipe *)tmp)->raw_text))
				free((((t_pipe *)tmp)->raw_text));
			free(tmp);
			pipe = pipe->next;
		}
		tmp = set;
		set = set->next;
		free(((t_set *)tmp)->raw_text);
		free((t_set *)tmp);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
