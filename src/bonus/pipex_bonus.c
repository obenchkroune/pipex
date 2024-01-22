/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:52:41 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/22 13:14:34 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	int		in_fd;
	int		out_fd;
	char	***commands;
	int		exit_status;

	check_errors(ac, av);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		commands = parse_commands(ac - 1, &av[1], env);
		in_fd = get_here_doc_fd(av[2]);
		out_fd = open(av[ac - 1], O_APPEND | O_WRONLY | O_CREAT, 0644);
		check_fd(in_fd, av[2]);
	}
	else
	{
		commands = parse_commands(ac, av, env);
		in_fd = open(av[1], O_RDONLY);
		out_fd = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0644);
		check_fd(in_fd, av[1]);
	}
	check_fd(out_fd, av[ac - 1]);
	exit_status = pipeline(in_fd, out_fd, commands, env);
	free_3d_tab(commands);
	return (exit_status);
}
