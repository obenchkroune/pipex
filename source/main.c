/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:28:24 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/22 08:45:37 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	char	***commands;
	int		infile;
	int		outfile;

	check_errors(ac, av);
	infile = check_fd(open(av[1], O_RDONLY), av[1]);
	outfile = check_fd(
			open(av[ac - 1], O_TRUNC | O_CREAT | O_WRONLY, 0664), av[ac - 1]);
	commands = parse_commands(ac, av, env);
	check_dup2(dup2(infile, 0), commands);
	close(infile);
	check_dup2(dup2(outfile, 1), commands);
	close(outfile);
	pipeline(commands, env);
	return (0);
}
