/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:52:41 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/30 22:00:08 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	int		in_fd;
	int		out_fd;
	char	***commands;
	int		exit_status;

	check_errors(ac, av);
	commands = parse_commands(ac, av, env);
	in_fd = open(av[1], O_RDONLY);
	check_fd(in_fd, av[1]);
	out_fd = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (check_fd(out_fd, av[ac - 1]) == -1)
	{
		free_3d_tab(commands);
		return (errno);
	}
	exit_status = pipeline(in_fd, out_fd, commands, env);
	close(in_fd);
	close(out_fd);
	while (wait(NULL) > 0)
		;
	free_3d_tab(commands);
	return (exit_status);
}
