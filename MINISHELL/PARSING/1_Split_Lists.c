/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_Split_Lists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 05:35:59 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/06 23:40:47 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

void	add_to_back(t_set *current, t_set **head)
{
	t_set	*cpy;

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

t_set	*make_sets(char **cpy, int *value, int *iterator, char *str)
{
	t_set	*current;

	if (*iterator < (int)ft_strlen(str))
		*iterator += 2;
	current = new_set();
	current->raw_text = *cpy;
	current->exit_val = *value;
	if (*str && str[*iterator - 1] == '|')
		*value = 1;
	else
		*value = 2;
	*cpy = NULL;
	return (current);
}

t_set	*find_sets(char *str)
{
	t_set	*ret;
	int		iterator;
	int		value;
	char	*cpy;
	int		inquote;

	cpy = NULL;
	value = 0;
	inquote = 0;
	ret = NULL;
	iterator = 0;
	while (str[iterator])
	{
		in_quotes(str[iterator], &inquote);
		if ((iterator == 0 || str[iterator - 1] != '\0'))
			cpy = add_character(str[iterator], cpy, 1);
		iterator++;
	}
	add_to_back(make_sets(&cpy, &value, &iterator, str), &ret);
	return (ret);
}
