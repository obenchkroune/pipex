/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:11:18 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/16 22:17:46 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	redirect_input(int fd, char ***commands)
{
	check_dup2(dup2(fd, 0), commands);
	close(fd);
}

void	redirect_output(int fd, char ***commands)
{
	check_dup2(dup2(fd, 1), commands);
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
		commands = parse_commands(ac - 1, &av[1], env);
		handle_here_doc(av[2], commands);
		o_flags |= O_APPEND;
	}
	else
	{
		infile = check_fd(open(av[1], O_RDONLY), av[1]);
		commands = parse_commands(ac, av, env);
		redirect_input(infile, commands);
		o_flags |= O_TRUNC;
	}
	outfile = check_fd(open(av[ac - 1], o_flags, 0664), av[ac - 1]);
	redirect_output(outfile, commands);
	pipeline(commands, env);
	free_3d_tab(commands);
	return (0);
}
