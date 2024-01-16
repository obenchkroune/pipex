/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:51:05 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/16 22:02:30 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_errors(int ac, char **av)
{
	if (ac > 1 && ft_strncmp(av[1], "here_doc", 9) == 0 && ac != 6)
	{
		ft_dprintf(2, PIPEX_HERE_DOC_USAGE);
		exit(errno);
	}
	if (ac < 5)
	{
		ft_dprintf(2, PIPEX_BONUS_USAGE);
		exit(errno);
	}
}

int	check_fd(int fd, char *file_name)
{
	if (fd < 0)
	{
		ft_dprintf(2, "pipex: %s: %s\n", strerror(errno), file_name);
		exit(errno);
	}
	return (fd);
}

int	check_dup2(int fd, char ***commands)
{
	if (fd < 0)
	{
		free_3d_tab(commands);
		exit(errno);
	}
	return (fd);
}
