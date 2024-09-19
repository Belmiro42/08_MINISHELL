/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_Heredoc_Expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:36:47 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

static bool	expand(char *text)
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

void	heredoc_expander(t_pipe *pipe)
{
	t_input	*inputs;
	char	*text;

	inputs = pipe->in;
	while (inputs)
	{
		text = inputs->token->token;
		inputs->expand = expand(text);
		inputs = inputs->next;
	}
}
