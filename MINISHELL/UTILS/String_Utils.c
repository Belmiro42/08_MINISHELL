/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   String_Utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:29:00 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

// ¡¡¡¡¡¡ ALL FUNCTIONS MODIFICADO INC STRJOIN ¡¡¡¡¡¡
// FUNCTION DESCRIPTION: arrlen
int	ft_arrlen(char **arr)
{
	int	ret;

	ret = 0;
	while (arr[ret])
		ret++;
	return (ret);
}

// TODO: Change to make easier
// FUNCTION DESCRIPTION: ft_isspace
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	else
		return (0);
}

// FUNCTION DESCRIPTION: in_quotes
// Whether we are in simple quotes or doubles quotes.
// 1 DENOTES WE ARE IN SIMPLE QUOTE
// 2 DENOTES WE ARE IN SIMPLE QUOTE
int	in_quotes(char c, int *quote)
{
	if (c == '\'' && *quote == 0)
		return (*quote = 1, 1);
	else if (c == '\'' && *quote == 1)
		return (*quote = 0, 1);
	if (c == '\"' && *quote == 0)
		return (*quote = 2, 1);
	else if (c == '\"' && *quote == 2)
		return (*quote = 0, 1);
	return (0);
}

// FUNCTION DESCRIPTION: add character
// adds a character to a string
char	*add_character(char character, char *string, bool free_string)
{
	char	*char_as_string;
	char	*result;

	char_as_string = malloc(sizeof(char) * 2);
	if (!char_as_string)
		return (NULL);
	char_as_string[0] = character;
	char_as_string[1] = '\0';
	result = ft_strjoin_mi(string, char_as_string, free_string, DEL);
	return (result);
}

// FUNCTION DESCRIPTION: STR_JOIN
// joins two strings together
// frees aswell if you want it to
char	*ft_strjoin_mi(char *s1, char *s2, bool free1, bool free2)
{
	char	*ptr;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	if (s2 && !s1)
		return (s2);
	if (s1 && !s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, len + 1);
	ft_strlcat(ptr, s2, len + 1);
	if (free1 && s1)
		free(s1);
	if (free2 && s2)
		free(s2);
	return (ptr);
}
