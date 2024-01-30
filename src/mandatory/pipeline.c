/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:57:29 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/30 22:10:23 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void \
	execute_command(t_pipeline pipeline, char ***cmd, char **env, int i)
{
	if (pipeline.input_fd == -1)
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
	if (access(cmd[i][0], X_OK) == 0)
	{
		execve(cmd[i][0], cmd[i] + 1, env);
		free_3d_tab(cmd);
		exit(errno);
	}
	else
	{
		ft_dprintf(2, "pipex: command not found: %s\n", cmd[0]);
		free_3d_tab(cmd);
		exit(127);
	}
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
			execute_command(pipeline, commands, env, i);
		update_pipeline(&pipeline, commands[i + 1] == NULL);
		i++;
	}
	waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}
