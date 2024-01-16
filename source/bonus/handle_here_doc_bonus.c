/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:13:17 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/16 22:14:44 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_here_doc(char *limiter, char **commands)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit(errno);
	}
	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(0);
		if (!line || strncmp(limiter, line, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	check_dup2(dup2(pipe_fd[0], 0), commands);
	close_pipes(pipe_fd);
}
