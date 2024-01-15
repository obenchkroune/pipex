/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:11:18 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/15 19:44:34 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_here_doc(char *limiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit(errno);
	}
	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		line = get_next_line(0);
		if (!line || strncmp(limiter, line, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	dup2(pipe_fd[0], 0);
	close_pipes(pipe_fd);
}

void	redirect_input(int fd)
{
	dup2(fd, 0);
	close(fd);
}

void	redirect_output(int fd)
{
	dup2(fd, 1);
	close(fd);
}

int	main(int ac, char **av, char **env)
{
	char	***commands;
	int		infile;
	int		outfile;
	int		o_flags;

	check_errors(ac, av);
	o_flags = O_CREAT | O_WRONLY;
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		handle_here_doc(av[2]);
		commands = parse_commands(ac - 1, &av[1], env);
		o_flags |= O_APPEND;
	}
	else
	{
		infile = check_fd(open(av[1], O_RDONLY), av[1]);
		redirect_input(infile);
		commands = parse_commands(ac, av, env);
		o_flags |= O_TRUNC;
	}
	outfile = check_fd(open(av[ac - 1], o_flags, 0664), av[ac - 1]);
	redirect_output(outfile);
	pipeline(commands, env);
	free_3d_tab(commands);
	return (0);
}
