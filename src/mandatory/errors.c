/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:44:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/03 01:54:43 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define PIPEX_USAGE "usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n"

void	check_errors(int ac)
{
	if (ac != 5)
	{
		ft_dprintf(2, PIPEX_USAGE);
		exit(1);
	}
}

void	ft_error(t_command **commands)
{
	int	error_number;

	error_number = errno;
	perror("");
	cleanup_commands(commands);
	exit (error_number);
}
