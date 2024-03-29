/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:05:32 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/03 01:48:58 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

int	get_here_doc_fd(char *limiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		perror("");
		exit(errno);
	}
	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		line = get_next_line(0);
		if (!line || ft_strncmp(limiter, line, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
