/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_Parse_Error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:26:47 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/14 15:06:53 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

static void	i_o_checker(int *ret, char *str)
{
	int		quote;
	int		pos;
	bool	i_o_valid;

	quote = 0;
	pos = 0;
	i_o_valid = 0;
	while (str[pos])
	{
		in_quotes(str[pos], &quote);
		if (!quote && (str[pos] == '<' || str[pos] == '>'))
		{
			pos++;
			if (str[pos - 1] == str[pos])
				pos++;
			while (ft_isspace(str[pos]))
				pos++;
			if (str[pos] == '|' || str[pos] == '<' || str[pos] == '>' \
			|| (str[pos] == '&' && str[pos + 1] == '&') || !str[pos])
				return ((void)(*ret = 1));
		}
		else
			pos++;
	}
}

static void	pipe_checker(int *ret, char *str)
{
	int		quote;
	int		pos;
	bool	pipe_valid;

	quote = 0;
	pos = -1;
	pipe_valid = 0;
	while (str[++pos])
	{
		in_quotes(str[pos], &quote);
		if (!(!quote && (str[pos] == '|' || (str[pos] == '&' && \
		str[pos + 1] == '&'))) && (quote || !ft_isspace(str[pos])))
			pipe_valid = 1;
		else if (!ft_isspace(str[pos]))
		{
			if (str[pos] && str[pos] == str[pos + 1])
				pos++;
			if (!pipe_valid)
				return ((void)(*ret = 1));
			pipe_valid = 0;
		}
	}
	return ((void)(*ret = !pipe_valid));
}

static void	quote_checker(int *ret, char *str)
{
	int	quote;

	quote = 0;
	while (*str)
		in_quotes(*(str++), &quote);
	if (quote != 0)
		*ret = 1;
}

static void	dbl_pipe(int *ret, char *str)
{
	int	quote;
	int	pos;

	quote = 0;
	pos = -1;
	while (str[++pos])
	{
		in_quotes(str[pos], &quote);
		if (!quote && str[pos] == '|' && str[pos + 1] == '|')
		{
			return ((void)(*ret = 1));
		}
	}
}

int	parse_error(char *str, t_env *environment)
{
	int		ret;
	char	*new_val;

	ret = 0;
	quote_checker(&ret, str);
	if (!ret)
		pipe_checker(&ret, str);
	if (!ret)
		i_o_checker(&ret, str);
	if (!ret)
		dbl_pipe(&ret, str);
	if (ret == 1)
	{
		ft_putstr_fd("Minishekk: parse error\n", 2);
		free(environment->value);
		new_val = ft_itoa(++ret);
		environment->value = new_val;
	}
	return (ret);
}
