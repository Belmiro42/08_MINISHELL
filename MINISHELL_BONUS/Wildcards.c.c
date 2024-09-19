/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wildcards.c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:11:01 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/19 23:49:03 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../MAIN/minishell_bonus.h"

static void is_match(char *pattern, char *file, char **ret)
{
	if (match(pattern, file, 0) && hidden_check(pattern, file))
	{
		*ret = ft_strjoin_mi(*ret, file, DEL, KEEP);
		*ret = ft_strjoin_mi(*ret, " ", DEL, KEEP);
	}
}

static void insert(char **ret, char *pattern)
{
	char *cpy;
	char *current;
	struct dirent *entry;
	DIR *dir;

	cpy = NULL;
	cpy = getcwd(cpy, 0);
	dir = opendir(cpy);
	free(cpy);
	entry = readdir(dir);
	while (entry != NULL)
	{
		current = strdup(entry->d_name);
		is_match(pattern, current, ret);
		if (*ret == (char *)1)
			return (free(current),
					free(pattern), (void)closedir(dir));
		entry = readdir(dir);
		free(current);
	}
	closedir(dir);
}

static void find_pattern(char *input, int *it, char **ret, int *start)
{
	char *pattern;
	char *new_ret;

	new_ret = ft_strdup("");
	while (*it >= 0 && !ft_isspace(input[*it]))
		(*it)--;
	*ret = ft_strjoin_mi(*ret, ft_substr(input, *start, ++(*it) - *start), DEL, DEL);
	*start = (*it)++;
	while (*it < (int)ft_strlen(input))
		(*it)++;
	pattern = ft_substr(input, *start, *it - *start);
	insert(&new_ret, pattern);
	if (new_ret == (char *)1)
		return (free(*ret), (void)(*ret = NULL));
	if (ft_strlen(new_ret) == 0)
		*ret = ft_strjoin_mi(*ret, pattern, DEL, KEEP);
	else
		*ret = ft_strjoin_mi(*ret, new_ret, DEL, KEEP);
	*start = *it;
	return (free(new_ret), free(pattern));
}

char *expand_wildcards_2(char *input)
{
	char *ret;
	int iterator;
	int start;
	int quote;

	ret = ft_strdup("");
	quote = 0;
	iterator = 0;
	start = 0;
	while (input[iterator] && iterator < (int)ft_strlen(input))
	{
		in_quotes(input[iterator], &quote);
		if (input[iterator] == '*' && !quote)
		{
			find_pattern(input, &iterator, &ret, &start);
			if (!ret)
				return (free(input), NULL);
		}
		iterator++;
	}
	ret = ft_strjoin_mi(ret, ft_substr(input, start, iterator - start), DEL, DEL);
	free(input);
	return (ret);
}