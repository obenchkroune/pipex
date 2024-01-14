/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:28:24 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/14 23:51:00 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	char	***commands;
	int		infile;
	int		outfile;

	if (ac != 5)
	{
		ft_dprintf(2, PIPEX_USAGE);
		return (1);
	}
	infile = check_fd(open(av[1], O_RDONLY), av[1]);
	outfile = check_fd(
			open(av[ac - 1], O_TRUNC | O_CREAT | O_WRONLY, 0664), av[ac - 1]);
	commands = parse_commands(ac, av, env);
	dup2(infile, 0);
	close(infile);
	dup2(outfile, 1);
	close(outfile);
	pipeline(commands, env);
	free_3d_tab(commands);
	return (0);
}
