/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:57:29 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/04 22:13:51 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>
#include <fcntl.h>
#include <libft.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static void \
	execute_command(t_pipeline pipeline, t_command **cmd, char **env, int i)
{
	if (access(cmd[i]->executable, F_OK) != 0)
	{
		ft_dprintf(2, "command not found: %s\n", cmd[i]->executable);
		cleanup_commands(cmd);
		exit(127);
	}
	if (pipeline.input_fd == -1 || pipeline.output_fd == -1)
		exit(ENOENT);
	if (!cmd[i + 1])
	{
		dup2(pipeline.output_fd, 1);
		close(pipeline.output_fd);
	}
	else
	{
		dup2(pipeline.pipe_fd[1], 1);
		close(pipeline.pipe_fd[1]);
		close(pipeline.pipe_fd[0]);
	}
	dup2(pipeline.input_fd, 0);
	close(pipeline.input_fd);
	execve(cmd[i]->executable, cmd[i]->argv, env);
	perror("");
	cleanup_commands(cmd);
	exit(EXIT_FAILURE);
}

static void	update_pipeline(t_pipeline *pipeline, int is_last)
{
	close(pipeline->input_fd);
	close(pipeline->pipe_fd[1]);
	if (is_last)
	{
		close(pipeline->pipe_fd[0]);
		close(pipeline->output_fd);
	}
	else
		pipeline->input_fd = pipeline->pipe_fd[0];
}

int	pipeline(int in_fd, int out_fd, t_command **commands, char **env)
{
	t_pipeline	pipeline;
	pid_t		pid;
	int			i;
	int			wstatus;

	pipeline.input_fd = in_fd;
	pipeline.output_fd = out_fd;
	i = 0;
	while (commands && commands[i])
	{
		if (commands[i + 1] && pipe(pipeline.pipe_fd) == -1)
			ft_error(commands);
		pid = fork();
		if (pid == -1)
			ft_error(commands);
		if (pid == 0)
			execute_command(pipeline, commands, env, i);
		update_pipeline(&pipeline, commands[i + 1] == NULL);
		i++;
	}
	waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}
