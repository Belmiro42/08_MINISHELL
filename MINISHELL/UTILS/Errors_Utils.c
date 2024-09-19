/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors_Utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:24:37 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

bool	no_errors(t_set *set)
{
	t_pipe	*tmp;

	while (set)
	{
		tmp = set->pipe;
		while (tmp)
		{
			if (tmp->raw_text == NULL)
				return (false);
			tmp = tmp->next;
		}
		set = set->next;
	}
	return (true);
}
