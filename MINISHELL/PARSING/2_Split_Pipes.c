/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_Split_Pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 05:26:28 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/06 20:19:25 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

// ¡¡TODO: PARSE ERROR

void	pipe_to_back(t_pipe *current, t_pipe **head)
{
	t_pipe	*cpy;

	cpy = *head;
	if (*head == NULL)
	{
		*head = current;
		return ;
	}
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = current;
}

t_pipe	*make_pipes(char **cpy, int *iterator)
{
	t_pipe	*current;

	*iterator += 1;
	current = new_pipe();
	current->raw_text = *cpy;
	*cpy = NULL;
	return (current);
}

void	find_pipes(t_set *set)
{
	t_pipe	*ret;
	int		iterator;
	int		inquote;
	char	*cpy;
	char	*str;

	cpy = NULL;
	inquote = 0;
	ret = NULL;
	iterator = -1;
	str = set->raw_text;
	while (str[++iterator])
	{
		in_quotes(str[iterator], &inquote);
		if (str[iterator] == '|' && inquote == 0)
			pipe_to_back(make_pipes(&cpy, &iterator), &ret);
		if ((iterator == 0 || str[iterator - 1] != '\0'))
			cpy = add_character(str[iterator], cpy, 1);
	}
	pipe_to_back(make_pipes(&cpy, &iterator), &ret);
	set->pipe = ret;
}
