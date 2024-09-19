/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_Make_Struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:41:50 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/06 21:29:14 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

static size_t	count_tokens(t_token *tokens)
{
	int		count;
	t_token	*real;

	count = 0;
	while (tokens)
	{
		real = tokens->real_tokens;
		while (real)
		{
			real = real->next;
			count++;
		}
		tokens = tokens->next;
	}
	return (count);
}

static void	add_to_args(t_pipe *pipe, size_t *count, t_token **real)
{
	pipe->args[(*count)++] = (*real)->token;
	(*real) = (*real)->next;
}

static int	convert_to_args(t_pipe *pipe)
{
	size_t	count;
	t_token	*tokens;
	t_token	*real;

	if (!pipe->token)
		return (0);
	tokens = pipe->token;
	tokens = pipe->token;
	count = count_tokens(tokens);
	pipe->args = ft_calloc((count + 1), sizeof(char *));
	if (!pipe->args)
		return (1);
	count = 0;
	while (tokens)
	{
		real = tokens->real_tokens;
		while (real)
		{
			if (real->token)
				add_to_args(pipe, &count, &real);
		}
		tokens = tokens->next;
	}
	pipe->args[count] = NULL;
	return (0);
}

int	parse(t_pipe *pipe, t_env *environment)
{
	(void)environment;
	tokenise(pipe, pipe->raw_text);
	if (quote_split_var_expansion(pipe, environment))
		return (4);
	if (word_splitting(pipe))
		return (4);
	if (fix_empty(pipe))
		return (4);
	if (convert_to_args(pipe))
		return (4);
	heredoc_expander(pipe);
	return (0);
}

t_set	*construct_parser_struct(char *input, t_env *environment)
{
	t_pipe	*pipe;
	t_set	*set;
	t_set	*set_cpy;

	(void)environment;
	set = NULL;
	set = find_sets(input);
	set_cpy = set;
	while (set_cpy != NULL)
	{
		find_pipes(set_cpy);
		pipe = set_cpy->pipe;
		while (pipe != NULL)
		{
			if (parse(pipe, environment))
			{
				free_struct_main(set, environment);
				return (NULL);
			}
			pipe = pipe->next;
		}
		set_cpy = set_cpy->next;
	}
	return (set);
}
