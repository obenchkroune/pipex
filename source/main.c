/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 03:31:55 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/03 05:33:37 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	redirect_io(t_pipex *pipex)
{
	int	in_fd;
	int	out_fd;

	in_fd = open(pipex->in_file, O_RDONLY);
	if (in_fd == -1)
	{
		ft_put_errno(pipex->in_file);
		clean_exit(pipex);
	}
	out_fd = open(pipex->out_file, O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (out_fd == -1)
	{
		ft_put_errno(pipex->out_file);
		clean_exit(pipex);
	}
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
