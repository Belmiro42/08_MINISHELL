/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_Tokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:45:14 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/06 20:28:47 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

char	*get_token(char *str, int *iterator)
{
	char	*token;
	int		quote;

	quote = 0;
	token = ft_strdup("");
	while (ft_isspace(str[*iterator]))
		(*iterator)++;
	while (((str[*iterator] && str[*iterator] != '<' && \
	str[*iterator] != '>') || quote != 0) && *iterator <= (int)strlen(str))
	{
		if (ft_isspace(str[*iterator]) && quote == 0)
			break ;
		in_quotes(str[*iterator], &quote);
		token = add_character(str[*iterator], token, 1);
		(*iterator)++;
	}
	if (!is_valid_arg(token, str, *iterator))
		return (free(token), NULL);
	return (token);
}

void	trigger_io(t_pipe *current, char *str, int *iterator, bool param)
{
	char	*filename;

	if (str[*iterator] == '>')
	{
		(*iterator)++;
		if (str[*iterator] == '>')
		{
			(*iterator)++;
			param = false;
		}
		filename = get_token(str, iterator);
		make_output_node(current, param, &filename);
	}
	else if (str[*iterator] == '<')
	{
		(*iterator)++;
		if (str[*iterator] == '<')
			(*iterator)++;
		else if (str[*iterator] == '>')
			(*iterator)++;
		else
			param = false;
		filename = get_token(str, iterator);
		make_input_node(current, param, &filename);
	}
}

void	make_token_node(t_pipe **current, char *token)
{
	t_token	*cpy;
	t_token	*f_current;

	f_current = new_token();
	f_current->token = token;
	if ((*current)->token)
	{
		cpy = (*current)->token;
		while (cpy->next)
			cpy = cpy->next;
		cpy->next = f_current;
	}
	else
		(*current)->token = f_current;
}

void	tokenise(t_pipe *current, char *str)
{
	int		iterator;
	int		quote;
	int		change;
	char	*token;

	iterator = 0;
	while (iterator < (int)strlen(str))
	{
		change = in_quotes(str[iterator], &quote);
		while (ft_isspace(str[iterator]))
			iterator++;
		if (str[iterator] == '<' || str[iterator] == '>')
			trigger_io(current, str, &iterator, true);
		else
		{
			token = get_token(str, &iterator);
			if (token)
				make_token_node(&current, token);
		}
	}
}
