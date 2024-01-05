/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 03:31:55 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/06 00:24:03 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

void	read_from_stdin(t_pipex *pipex)
{
	char	buffer[100];
	int		bytes;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		clean_exit(pipex);
	}
	while (true)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		bytes = read(STDIN_FILENO, buffer, 100);
		if (ft_strncmp(buffer, pipex->limiter, ft_strlen(pipex->limiter)) == 0)
			break ;
		if (bytes > 0)
			write(fd[1], buffer, bytes);
	}
	pipex->fdd = fd[0];
	close(fd[1]);
}

void	handle_file_error(char *file_name, int fd, t_pipex *pipex)
{
	if (fd == -1)
	{
		ft_put_errno(file_name);
		clean_exit(pipex);
	}
}

void	redirect_io(t_pipex *pipex)
{
	int	in_fd;
	int	out_fd;

	if (pipex->here_doc)
	{
		read_from_stdin(pipex);
		out_fd = open(pipex->out_file, O_APPEND | O_WRONLY | O_CREAT, 0666);
	}
	else
	{
		in_fd = open(pipex->in_file, O_RDONLY);
		handle_file_error(pipex->in_file, in_fd, pipex);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		out_fd = open(pipex->out_file, O_TRUNC | O_WRONLY | O_CREAT, 0666);
	}
	handle_file_error(pipex->out_file, out_fd, pipex);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	if (ac > 1 && ac != 6 && ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		ft_putendl_fd(PIPEX_HERE_DOC_USAGE, 2);
		return (EXIT_FAILURE);
	}
	if (ac < 5)
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
