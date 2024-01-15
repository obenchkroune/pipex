/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:30:00 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/15 19:44:49 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void \
	execute_command(t_pipeline pipeline, char **cmd, char **env, int is_last)
{
	if (pipeline.fd != -1)
	{
		dup2(pipeline.fd, 0);
		close(pipeline.fd);
	}
	if (!is_last)
		dup2(pipeline.pipe_fds[1], 1);
	close_pipes(pipeline.pipe_fds);
	execve(cmd[0], &cmd[1], env);
	exit(errno);
}

static void	wait_for_command(t_pipeline *pipeline, int is_last)
{
	wait(NULL);
	pipeline->fd = pipeline->pipe_fds[0];
	close(pipeline->pipe_fds[1]);
	if (is_last)
		close(pipeline->pipe_fds[0]);
}

static void	ft_error(char ***commands)
{
	ft_dprintf(2, "pipex: %s\n", strerror(errno));
	free_3d_tab(commands);
	exit(errno);
}

void	pipeline(char ***commands, char **env)
{
	t_pipeline	pipeline;
	pid_t		pid;

	pipeline.fd = -1;
	while (*commands)
	{
		if (pipe(pipeline.pipe_fds) < 0)
			ft_error(commands);
		pid = fork();
		if (pid == 0)
			execute_command(pipeline, *commands, env, !*(commands + 1));
		else if (pid > 0)
		{
			wait_for_command(&pipeline, !*(commands + 1));
			commands++;
		}
		else
			ft_error(commands);
	}
}
