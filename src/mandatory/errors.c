/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:44:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/22 12:47:01 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PIPEX_USAGE "pipex: usage: ./pipex [infile] [cmd1] [cmd2] [outfile]\n"

void	check_errors(int ac, char **av)
{
	if (ac != 5)
	{
		ft_dprintf(2, PIPEX_USAGE);
		exit(1);
	}
	while (*av)
	{
		if (strlen(*av) == 0)
		{
			ft_dprintf(2, PIPEX_USAGE);
			exit(1);
		}
		av++;
	}
}

void	ft_error(char *s, char ***commands)
{
	int	error_number;

	error_number = errno;
	perror(s);
	free_3d_tab(commands);
	exit (error_number);
}
