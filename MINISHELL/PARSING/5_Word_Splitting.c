/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_Word_Splitting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:33:25 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/06 21:10:38 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

static int	real_token(char **token, t_token *tk)
{
	t_token	*new;
	t_token	*iter;

	if (ft_strlen(*token) == 0)
		return (0);
	new = new_token();
	if (!new)
		return (1);
	new->token = *token;
	*token = ft_strdup("");
	if (!*token)
		return (free_token(new), 1);
	if (!tk->real_tokens)
		return ((void)(tk->real_tokens = new), 0);
	iter = tk->real_tokens;
	while (iter->next)
		iter = iter->next;
	iter->next = new;
	return (0);
}

static int	split_tokens(t_token *tk, char **token, t_token *to_be_split)
{
	char	*curr_str;

	while (to_be_split)
	{
		curr_str = to_be_split->token;
		while (*curr_str)
		{
			if (*curr_str == ' ' && to_be_split->inquote == 0)
			{
				if (real_token(token, tk))
					return (1);
			}
			else
			{
				*token = add_character(*curr_str, *token, DEL);
				if (!token)
					return (1);
			}
			curr_str++;
		}
		to_be_split = to_be_split->next;
	}
	if (real_token(token, tk))
		return (1);
	return (0);
}

static int	split_by_real_space(t_token *tk)
{
	char	*token;
	t_token	*to_be_split;

	to_be_split = tk->quoted_expanded;
	token = ft_strdup("");
	if (!token)
		return (1);
	if (split_tokens(tk, &token, to_be_split))
		return (free (token), 1);
	free(token);
	return (0);
}

static int	word_splitting_redirects(t_pipe *pipe)
{
	t_input		*input;
	t_output	*output;

	input = pipe->in;
	while (input)
	{
		if (split_by_real_space(input->token))
			return (1);
		if (input->token->real_tokens)
			input->filename = ft_strdup(input->token->real_tokens->token);
		input = input->next;
	}
	output = pipe->out;
	while (output)
	{
		if (split_by_real_space(output->token))
			return (1);
		if (output->token->real_tokens)
			output->filename = ft_strdup(output->token->real_tokens->token);
		output = output->next;
	}
	return (0);
}

int	word_splitting(t_pipe *pipe)
{
	t_token	*iter;
	t_token	*token;

	iter = pipe->token;
	while (iter)
	{
		token = iter->quoted_expanded;
		if (split_by_real_space(iter))
			return (1);
		iter = iter->next;
	}
	if (word_splitting_redirects(pipe))
		return (1);
	return (0);
}
