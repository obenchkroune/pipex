/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:11:18 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/13 23:01:44 by obenchkr         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
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

int	main(int ac, char **av, char **env)
{
	char	***commands;
	int		infile;
	int		outfile;

	check_errors(ac, av);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		handle_here_doc(av[2]);
		commands = parse_commands(ac - 1, &av[1], env);
	}
	else
	{
		infile = check_fd(open(av[1], O_RDONLY), av[1]);
		dup2(infile, 0);
		close(infile);
		commands = parse_commands(ac, av, env);
	}
	outfile = check_fd(
			open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0664), av[ac - 1]);
	dup2(outfile, 1);
	close(outfile);
	pipeline(commands, env);
	free_3d_tab(commands);
	return (0);
}
