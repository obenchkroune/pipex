/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:44:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/22 13:04:33 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#define PIPEX_USAGE \
"pipex: usage: ./pipex_bonus [infile] [cmd1] [cmd2] ... [cmdn] [outfile]\n"
#define HEREDOC_USAGE \
"pipex: usage: ./pipex_bonus here_doc [LIMITER] [cmd1] [cmd2] [outfile]\n"

// TODO: check here_doc errors
void	check_errors(int ac, char **av)
{
	if (ac > 1 && ft_strncmp(av[1], "here_doc", 9) == 0 && ac != 6)
	{
		ft_dprintf(2, HEREDOC_USAGE);
		exit(1);
	}
	if (ac < 5)
	{
		ft_dprintf(2, PIPEX_USAGE);
		exit(1);
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
