/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution_Utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 07:19:47 by razamora          #+#    #+#             */
/*   Updated: 2024/09/05 22:51:04 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

char	*ft_find_path(char **envp)
{
	char	*value_path;

	while (*envp != NULL)
	{
		value_path = *envp++;
		if (ft_strncmp(value_path, "PATH=", 5) == 0)
		{
			value_path = value_path + 5;
			return (value_path);
		}
	}
	return (NULL);
}

void	ft_freedbl(char **twodimmalloc)
{
	int	iterator;

	iterator = 0;
	while (twodimmalloc[iterator])
		free(twodimmalloc[iterator++]);
	free(twodimmalloc);
}

int	finaly_openfile(char **av, int argc)
{
	int	fd_out;

	if (ft_strncmp("heredoc", av[1], 8) == 0)
		fd_out = open_file(av[argc - 1], 2);
	else
		fd_out = open_file(av[argc - 1], 1);
	return (fd_out);
}

int	open_file(char *file, int type)
{
	int	ret;

	if (type == 0)
		ret = open(file, O_RDONLY, 0644);
	if (type == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (type == 2)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (ret);
}

void	ft_close_fd_final(int fd, int *file_pipe)
{
	close(fd);
	close(file_pipe[0]);
	close(file_pipe[1]);
}
