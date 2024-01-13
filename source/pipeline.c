/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:30:00 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/13 21:30:08 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_command(int pipe_fd[2], char **command, char **env, int is_last)
{
	if (!is_last)
		dup2(pipe_fd[1], 1);
	close_pipes(pipe_fd);
	execve(command[0], &command[1], env);
	exit(1);
}

static void	wait_for_command(int pipe_fd[2], int *fd_ptr, int is_last)
{
	wait(NULL);
	*fd_ptr = pipe_fd[0];
	close(pipe_fd[1]);
	if (is_last)
		close(pipe_fd[0]);
}

void	pipeline(char ***commands, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		fd;

	fd = -1;
	while (*commands)
	{
		if (pipe(pipe_fd) < 0)
			return ;
		pid = fork();
		if (pid == 0)
		{
			if (fd != -1)
				dup2(fd, 0);
			close(fd);
			execute_command(pipe_fd, *commands, env, !*(commands + 1));
		}
		else if (pid > 0)
		{
			wait_for_command(pipe_fd, &fd, !*(commands + 1));
			commands++;
		}
	}
}