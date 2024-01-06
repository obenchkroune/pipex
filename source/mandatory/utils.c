/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 03:39:14 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/06 01:52:56 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_exec_path(char *cmd, t_pipex *pipex)
{
	char	*bin_path;
	size_t	i;
	char	*slash_cmd;

	i = 0;
	slash_cmd = ft_strjoin("/", cmd);
	while (pipex->env_path[i] != NULL)
	{
		bin_path = ft_strjoin(pipex->env_path[i], slash_cmd);
		if (access(bin_path, F_OK | X_OK) == 0)
			break ;
		free(bin_path);
		bin_path = NULL;
		i++;
	}
	free(slash_cmd);
	if (bin_path == NULL)
	{
		ft_put_error(PIPEX_NO_CMD, cmd);
		clean_exit(pipex);
	}
	return (bin_path);
}

void	init_pipex(t_pipex **data, int ac, char **av, char **envp)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		exit(EXIT_FAILURE);
	ft_bzero(pipex, sizeof(t_pipex));
	pipex->in_file = av[1];
	pipex->out_file = av[ac - 1];
	pipex->envp = envp;
	pipex->env_path = parse_path(envp);
	pipex->commands = parse_commands(ac, av);
	pipex->cmds_path = parse_executables(pipex->commands, pipex);
	pipex->fdd = STDIN_FILENO;
	*data = pipex;
}

void	pipeline(t_pipex *pipex)
{
	pid_t	pid;
	size_t	i;

	i = 0;
	while (pipex->commands[i] != NULL)
	{
		pipe(pipex->pipe_fds);
		pid = fork();
		if (pid == 0)
		{
			dup2(pipex->fdd, STDIN_FILENO);
			if (pipex->commands[i + 1] != NULL)
				dup2(pipex->pipe_fds[1], STDOUT_FILENO);
			close(pipex->pipe_fds[0]);
			if (execve(pipex->cmds_path[i], pipex->commands[i], pipex->envp) == -1)
				exit(errno);
		}
		else
		{
			wait(NULL);
			pipex->fdd = pipex->pipe_fds[0];
			close(pipex->pipe_fds[1]);
			i++;
		}
	}
}
