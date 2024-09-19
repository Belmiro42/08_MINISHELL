/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Liberation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:20:32 by razamora          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

void	free_struct_main(t_set *set, t_env *env)
{
	free_parser_struct(set);
	free_env(env);
	exit(4);
}
