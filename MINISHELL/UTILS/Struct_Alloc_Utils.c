/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Struct_Alloc_Utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 00:55:12 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

t_set	*new_set(void)
{
	t_set	*new_set;

	new_set = malloc(sizeof(t_set));
	new_set->pipe = NULL;
	new_set->next = NULL;
	new_set->exit_val = 0;
	new_set->raw_text = NULL;
	return (new_set);
}

t_pipe	*new_pipe(void)
{
	t_pipe	*new_pipe;

	new_pipe = malloc(sizeof(t_pipe));
	new_pipe->raw_text = NULL;
	new_pipe->args = NULL;
	new_pipe->next = NULL;
	new_pipe->in = NULL;
	new_pipe->out = NULL;
	new_pipe->token = NULL;
	return (new_pipe);
}

t_token	*new_token(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	new_token->inquote = 0;
	new_token->real_tokens = NULL;
	new_token->quoted_expanded = NULL;
	new_token->next = NULL;
	new_token->token = NULL;
	return (new_token);
}

t_input	*new_input(void)
{
	t_input	*new_input;

	new_input = malloc(sizeof(t_input));
	new_input->heredoc = 0;
	new_input->expand = 0;
	new_input->filename = NULL;
	new_input->tmp = NULL;
	new_input->next = NULL;
	new_input->token = NULL;
	return (new_input);
}

t_output	*new_output(void)
{
	t_output	*new_output;

	new_output = malloc(sizeof(t_output));
	new_output->append = 0;
	new_output->filename = NULL;
	new_output->next = NULL;
	new_output->token = NULL;
	return (new_output);
}
