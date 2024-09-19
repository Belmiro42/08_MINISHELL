/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenise_Utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:58:19 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

void	make_output_node(t_pipe *current, bool param, char **filename)
{
	t_output	*cpy;
	t_output	*f_current;

	f_current = new_output();
	f_current->append = !param;
	f_current->token = new_token();
	f_current->token->token = strdup(*filename);
	free(*filename);
	*filename = NULL;
	if (current->out)
	{
		cpy = current->out;
		while (cpy->next)
			cpy = cpy->next;
		cpy->next = f_current;
	}
	else
		current->out = f_current;
}

bool	check_if_valid(char *filename)
{
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, W_OK) == 0)
			return (true);
		return (false);
	}
	else
		return (true);
}

char	*create_tmp_file(void)
{
	static int	count = 0;
	char		*file_tmp;

	file_tmp = ft_strjoin_mi("/tmp/tmp", ft_itoa(count++), KEEP, DEL);
	while (!check_if_valid(file_tmp))
	{
		free(file_tmp);
		file_tmp = ft_strjoin_mi("/tmp/tmp", ft_itoa(count++), KEEP, DEL);
	}
	return (file_tmp);
}

void	make_input_node(t_pipe *current, bool param, char **filename)
{
	t_input	*cpy;
	t_input	*f_current;

	f_current = new_input();
	f_current->heredoc = param;
	f_current->token = new_token();
	f_current->token->token = ft_strdup(*filename);
	if (f_current->heredoc == 1)
		f_current->tmp = create_tmp_file();
	free(*filename);
	*filename = NULL;
	if (current->in)
	{
		cpy = current->in;
		while (cpy->next)
			cpy = cpy->next;
		cpy->next = f_current;
	}
	else
		current->in = f_current;
}

bool	is_valid_arg(char *token, char *str, int iterator)
{
	if (ft_strlen(token) != 0 || ((str[iterator - 1] == '\'' \
	|| str[iterator - 1] == '\"') && str[iterator - 1] == str[iterator - 2]))
		return (true);
	return (false);
}
