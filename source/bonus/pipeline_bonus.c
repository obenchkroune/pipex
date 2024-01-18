/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:30:00 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/18 12:43:31 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void \
	execute_command(t_pipeline pipeline, char **cmd, char **env, bool is_last)
{
	if (access(cmd[0], X_OK) != 0)
		exit(errno);
	if (pipeline.fd != -1)
	{
		dup2(pipeline.fd, 0);
		close(pipeline.fd);
	}
	if (!is_last)
	{
		dup2(pipeline.pipe_fds[1], 1);
		close(pipeline.pipe_fds[1]);
	}
	close_pipes(pipeline.pipe_fds);
	execve(cmd[0], &cmd[1], env);
	exit(EXIT_FAILURE);
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
		if (pid < 0)
			ft_error(commands);
		else if (pid == 0)
			execute_command(pipeline, *commands, env, !*(commands + 1));
		close(pipeline.pipe_fds[1]);
		if (pipeline.fd != -1)
			close(pipeline.fd);
		pipeline.fd = pipeline.pipe_fds[0];
		if (*(commands + 1) == NULL)
			close(pipeline.pipe_fds[0]);
		commands++;
	}
	wait(NULL);
}
