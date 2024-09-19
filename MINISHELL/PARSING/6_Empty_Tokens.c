/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_Empty_Tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 01:47:47 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/06 21:21:07 by razamora         ###   ########.fr       */
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
	void		*tmp;

	tmp = (void *)pipe->in;
	while (tmp)
	{
		if (find_empty_tokens(((t_input *)tmp)->token))
			return (1);
		tmp = (void *)((t_input *)tmp)->next;
	}
	tmp = (void *)pipe->out;
	while (tmp)
	{
		if (find_empty_tokens(((t_output *)tmp)->token))
			return (1);
		tmp = (void *)((t_output *)tmp)->next;
	}
	tmp = (void *)pipe->token;
	while (tmp)
	{
		if (find_empty_tokens((t_token *)tmp))
			return (1);
		tmp = (void *)((t_token *)tmp)->next;
	}
	return (0);
}
