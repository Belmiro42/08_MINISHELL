/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ambiguous_Redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 01:44:28 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

void	ambiguous_redirect(t_input *input, t_output *output)
{
	if (input)
	{
		if (input->token->real_tokens->next)
		{
			write(2, "Minishekk: ", 11);
			write(2, (input->token->token), ft_strlen(input->token->token));
			write(2, ": ambiguous redirect\n", 21);
			exit(EXIT_FAILURE);
		}
	}
	if (output)
	{
		if (output->token->real_tokens->next)
		{
			write(2, "Minishekk: ", 11);
			write(2, (output->token->token), ft_strlen(output->token->token));
			write(2, ": ambiguous redirect\n", 21);
			exit(EXIT_FAILURE);
		}
	}
}
