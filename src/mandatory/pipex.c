/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:52:41 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/03 01:38:47 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <libft.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	int			in_fd;
	int			out_fd;
	t_command	**commands;
	int			exit_status;

	check_errors(ac);
	in_fd = open(av[1], O_RDONLY);
	check_fd(in_fd, av[1]);
	out_fd = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	check_fd(out_fd, av[ac - 1]);
	commands = parse_commands(ac, av, env);
	exit_status = pipeline(in_fd, out_fd, commands, env);
	close(in_fd);
	close(out_fd);
	while (wait(NULL) > 0)
		;
	cleanup_commands(commands);
	return (exit_status);
}
