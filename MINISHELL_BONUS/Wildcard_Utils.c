/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wildcard_Utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 03:21:02 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/19 23:47:48 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../MAIN/minishell_bonus.h"

bool ft_spsp(char *str, int iterator, int dir)
{
	if (str[iterator] == '<' || str[iterator] == '>' || str[iterator] == '|' || str[iterator] == ' ')
		return (true);
	if (dir == 1 && iterator < (int)ft_strlen(str) && dir == 1)
		if (str[iterator] == '&' && str[iterator + 1] == '&')
			return (true);
	if (dir == -1 && iterator > 0)
		if (str[iterator] == '&' && str[iterator - 1] == '&')
			return (true);
	return (false);
}

bool match(char *pattern, char *file, int quote)
{
	int change;

	if (*pattern == '\0' && *file == '\0')
		return (true);
	if (*pattern == '\0')
		return (false);
	change = in_quotes(*pattern, &quote);
	if (change == 1)
		return (match(pattern + 1, file, quote));
	if (*pattern == '*' && !quote && match(pattern + 1, file, quote))
		return (true);
	if (*pattern == '*' && *file != '\0' && !quote && match(pattern, file + 1, quote))
		return (true);
	if (*pattern == *file && match(pattern + 1, file + 1, quote))
		return (true);
	return (false);
}

bool hidden_check(char *pattern, char *file)
{
	bool char_check;
	int quote;
	bool change;

	char_check = false;
	quote = 0;
	change = 0;
	while (*pattern)
	{
		change = in_quotes(*pattern, &quote);
		if (*(pattern++) != '*' && !change)
			return (true);
		else if (file[0] == '.')
			return (false);
	}
	return (true);
}