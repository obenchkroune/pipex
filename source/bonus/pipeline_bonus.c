/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:30:00 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/22 09:09:33 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void \
	execute_command(t_pipeline pipeline, char **cmd, char **env, bool is_last)
{
	if (access(cmd[0], X_OK) != 0)
	{
		ft_dprintf(2, "pipex: command not found: %s\n", cmd[1]);
		exit(errno);
	}
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
	if (execve(cmd[0], &cmd[1], env) == -1)
		exit(errno);
}

static void	update_pipeline(t_pipeline *pipeline, bool is_last)
{
	close(pipeline->pipe_fds[1]);
	if (pipeline->fd != -1)
		close(pipeline->fd);
	pipeline->fd = pipeline->pipe_fds[0];
	if (is_last)
		close(pipeline->pipe_fds[0]);
}

static void	ft_error(char ***commands)
{
	ft_dprintf(2, "pipex: %s\n", strerror(errno));
	free_3d_tab(commands);
	exit(EXIT_FAILURE);
}

static void	wait_for_childs(char ***commands)
{
	pid_t	pid;
	int		wstatus;

	pid = wait(&wstatus);
	while (pid > 0)
	{
		pid = wait(&wstatus);
	}
	free_3d_tab(commands);
	exit(WEXITSTATUS(wstatus));
}

void	pipeline(char ***commands, char **env)
{
	t_pipeline	pipeline;
	pid_t		pid;
	int			i;

	pipeline.fd = -1;
	i = 0;
	while (commands[i])
	{
		if (pipe(pipeline.pipe_fds) < 0)
			ft_error(commands);
		pid = fork();
		if (pid < 0)
			ft_error(commands);
		else if (pid == 0)
			execute_command(pipeline, commands[i], env, !commands[i + 1]);
		else
			update_pipeline(&pipeline, commands[i + 1] == NULL);
		i++;
	}
	wait_for_childs(commands);
}
