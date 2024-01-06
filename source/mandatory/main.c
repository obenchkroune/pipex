/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 03:31:55 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/06 01:37:37 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	get_in_file(t_pipex *pipex)
{
	int	fd;

	if (access(pipex->in_file, F_OK) != 0)
	{
		fd = open(pipex->in_file, O_RDONLY);
		if (fd != 0)
			return (fd);
	}
	ft_put_errno(pipex->in_file);
	clean_exit(pipex);
	return (-1);
}

int	get_out_file(t_pipex *pipex)
{
	int	fd;

	if (access(pipex->out_file, F_OK) != 0)
	{
		fd = open(pipex->out_file, O_TRUNC | O_WRONLY | O_CREAT, 0666);
		if (fd != 0)
			return (fd);
	}
	ft_put_errno(pipex->out_file);
	clean_exit(pipex);
	return (-1);
}

void	redirect_io(t_pipex *pipex)
{
	int	in_fd;
	int	out_fd;

	in_fd = get_in_file(pipex);
	out_fd = get_out_file(pipex);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	if (ac != 5)
	{
		ft_putendl_fd(PIPEX_USAGE, 2);
		return (EXIT_FAILURE);
	}
	init_pipex(&pipex, ac, av, env);
	redirect_io(pipex);
	pipeline(pipex);
	cleanup_pipex(pipex);
	return (EXIT_SUCCESS);
}
