/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_Quote_Split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:56:55 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/06 20:58:59 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

static int	add_node(t_token *token, char **output, int quote)
{
	t_token	*next;
	t_token	*link;

	if (ft_strlen(*output) == 0)
		return (0);
	next = new_token();
	if (!next)
		return (1);
	next->inquote = quote;
	next->token = *output;
	next->next = NULL;
	*output = ft_strdup("");
	if (!*output)
		return (free(token), 1);
	if (!token->quoted_expanded)
		return ((void)(token->quoted_expanded = next), 0);
	link = token->quoted_expanded;
	while (link->next)
		link = link->next;
	link->next = next;
	return (0);
}

static int	sep_by_qt(t_token *token, char *input, int quote, int change)
{
	char	*output;
	int		tmp_quote;

	output = ft_calloc(1, sizeof(char));
	while (*(++input))
	{
		tmp_quote = quote;
		change = in_quotes(*input, &quote);
		if (change)
		{
			if (add_node(token, &output, tmp_quote))
				return (free(output), 1);
		}
		else
		{
			output = add_character(*input, output, DEL);
			if (!output)
				return (1);
		}
	}
	if (add_node(token, &output, tmp_quote))
		return (free(output), 1);
	free(output);
	return (0);
}

static void	quote_split_var_expansion_out(t_pipe *pipe, t_env *env)
{
	t_output	*all_outputs;
	t_token		*iter_qe;
	int			change;
	int			quote;

	quote = 0;
	change = 0;
	all_outputs = pipe->out;
	while (all_outputs)
	{
		if (all_outputs->token->token)
			sep_by_qt(all_outputs->token, all_outputs->token->token - 1,
				quote, change);
		iter_qe = all_outputs->token->quoted_expanded;
		while (iter_qe)
		{
			if (iter_qe->inquote != 1)
				iter_qe->token = variable_expansion(iter_qe->token, env);
			iter_qe = iter_qe->next;
		}
		all_outputs = all_outputs->next;
	}
}

static void	quote_split_var_expansion_in(t_pipe *pipe, t_env *env)
{
	t_input	*all_inputs;
	t_token	*iter_qe;
	int		change;
	int		quote;

	quote = 0;
	change = 0;
	all_inputs = pipe->in;
	while (all_inputs)
	{
		if (all_inputs->token->token)
			sep_by_qt(all_inputs->token, all_inputs->token->token - 1,
				quote, change);
		iter_qe = all_inputs->token->quoted_expanded;
		while (iter_qe)
		{
			if (iter_qe->inquote != 1 && all_inputs->heredoc == 0)
				iter_qe->token = variable_expansion(iter_qe->token, env);
			iter_qe = iter_qe->next;
		}
		all_inputs = all_inputs->next;
	}
	quote_split_var_expansion_out(pipe, env);
}

int	quote_split_var_expansion(t_pipe *pipe, t_env *env)
{
	t_token	*iter;
	t_token	*iter_qe;
	int		change;
	int		quote;

	quote = 0;
	change = 0;
	iter = pipe->token;
	while (iter)
	{
		if (iter->token)
		{
			sep_by_qt(iter, iter->token - 1, quote, change);
		}
		iter_qe = iter->quoted_expanded;
		while (iter_qe)
		{
			if (iter_qe->inquote != 1)
				iter_qe->token = variable_expansion(iter_qe->token, env);
			iter_qe = iter_qe->next;
		}
		iter = iter->next;
	}
	quote_split_var_expansion_in(pipe, env);
	return (0);
}
