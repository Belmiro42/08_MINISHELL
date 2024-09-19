/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_File.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:37:00 by razamora          #+#    #+#             */
/*   Updated: 2024/09/11 17:36:43 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MAIN/minishell.h"

void	close_last_middle_fd(int *file_pipe, int *middle_file)
{
	close(file_pipe[1]);
	close(file_pipe[0]);
	close(middle_file[1]);
	close(middle_file[0]);
	bash();
}

int	close_middle_fd(int *file_pipe, int *middle_file)
{
	close(file_pipe[1]);
	close(file_pipe[0]);
	close(middle_file[1]);
	close(middle_file[0]);
	return (1);
}

void	msm_heredoc(char *limiter, int line)
{
	char	*new;
	char	*msg;
	char	*msg2;

	msg = "\nwarning: here-document at line ";
	msg2 = " delimited by end-of-file (wanted `";
	new = ft_strjoin_mi(msg, ft_itoa(line), KEEP, DEL);
	if (!new)
		ft_putendl_fd("malloc failed", 2);
	new = ft_strjoin_mi(new, msg2, DEL, KEEP);
	if (!new)
		ft_putendl_fd("malloc failed", 2);
	new = ft_strjoin_mi(new, limiter, DEL, KEEP);
	if (!new)
		ft_putendl_fd("malloc failed", 2);
	new = ft_strjoin_mi(new, "')", DEL, KEEP);
	if (!new)
		ft_putendl_fd("malloc failed", 2);
	ft_putendl_fd(new, 2);
	free(new);
}

int	handle_outfile(t_output *file)
{
	int	fd;

	ambiguous_redirect(NULL, file);
	fd = 0;
	while (file)
	{
		if (file->append == 1)
			fd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else if (file->append == 0)
			fd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
		{
			perror(file->filename);
			return (fd);
		}
		dup2(fd, 1);
		close(fd);
		file = file->next;
	}
	return (fd);
}

int	handle_infile(t_input *file)
{
	int		fd;
	char	*filename;

	ambiguous_redirect(file, NULL);
	fd = 0;
	while (file)
	{
		if (file->heredoc == 1)
			filename = file->tmp;
		else
			filename = file->filename;
		fd = open_file(filename, 0);
		if (fd < 0)
			return (perror(filename), fd);
		if (!file->next)
			dup2(fd, 0);
		close(fd);
		file = file->next;
	}
	return (fd);
}
