/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:30:00 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/14 02:22:18 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	execute_command(int pipe_fd[2], char **cmd, char **env, int is_last)
{
	if (!is_last)
		dup2(pipe_fd[1], 1);
	close_pipes(pipe_fd);
	execve(cmd[0], &cmd[1], env);
	exit(EXIT_FAILURE);
}

static void	wait_for_command(int pipe_fd[2], int *fd_ptr, int is_last)
{
	wait(NULL);
	*fd_ptr = pipe_fd[0];
	close(pipe_fd[1]);
	if (is_last)
		close(pipe_fd[0]);
}

static void	ft_error(char ***commands)
{
	ft_dprintf(2, "pipex: %s\n", strerror(errno));
	free_3d_tab(commands);
	exit(errno);
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
			ft_error(commands);
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
		else
			ft_error(commands);
	}
}
