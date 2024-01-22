/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:57:29 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/22 12:56:33 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void \
	execute_command(t_pipeline pipeline, char **cmd, char **env, int is_last)
{
	if (pipeline.input_fd == -1)
		exit(ENOENT);
	if (is_last)
	{
		dup2(pipeline.output_fd, 1);
		close(pipeline.output_fd);
	}
	else
	{
		dup2(pipeline.pipe_fd[1], 1);
		close(pipeline.pipe_fd[1]);
	}
	dup2(pipeline.input_fd, 0);
	close(pipeline.input_fd);
	if (access(cmd[0], X_OK) == 0)
	{
		execve(cmd[0], cmd + 1, env);
		exit(errno);
	}
	else
	{
		ft_dprintf(2, "pipex: command not found: %s\n", cmd[0]);
		exit(127);
	}
}

static void	update_pipeline(t_pipeline *pipeline, int is_last)
{
	close(pipeline->input_fd);
	close(pipeline->pipe_fd[1]);
	pipeline->input_fd = pipeline->pipe_fd[0];
	if (is_last)
		close(pipeline->pipe_fd[0]);
}

int	pipeline(int in_fd, int out_fd, char ***commands, char **env)
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
		if (pipe(pipeline.pipe_fd) == -1)
			ft_error("pipe", commands);
		pid = fork();
		if (pid == -1)
			ft_error("fork", commands);
		if (pid == 0)
			execute_command(pipeline, commands[i], env, !commands[i + 1]);
		update_pipeline(&pipeline, commands[i + 1] == NULL);
		i++;
	}
	waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}
