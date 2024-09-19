/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_Empty_Tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 01:47:47 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

static bool	check_for_commas(char *text)
{
	int	quote;

	quote = 0;
	while (*text)
	{
		in_quotes(*text, &quote);
		if (quote)
			return (true);
		text++;
	}
	return (false);
}

static int	find_empty_tokens(t_token *node)
{
	char	*empty;

	if (!node->real_tokens && check_for_commas(node->token))
	{
		empty = ft_strdup("");
		if (!empty)
			return (1);
		node->real_tokens = new_token();
		if (!node->real_tokens)
			return (free(empty), 1);
		node->real_tokens->token = empty;
	}
	return (0);
}

int	fix_empty(t_pipe *pipe)
{
	t_token		*args;
	t_input		*inputs;
	t_output	*output;

	inputs = pipe->in;
	while (inputs)
	{
		if (find_empty_tokens(inputs->token))
			return (1);
		inputs = inputs->next;
	}
	output = pipe->out;
	while (output)
	{
		if (find_empty_tokens(output->token))
			return (1);
		output = output->next;
	}
	args = pipe->token;
	while (args)
	{
		if (find_empty_tokens(args))
			return (1);
		args = args->next;
	}
	return (0);
}
