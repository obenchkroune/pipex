/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:51:05 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/22 08:58:43 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_errors(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5)
	{
		ft_dprintf(2, PIPEX_USAGE);
		exit(1);
	}
	while (i < ac)
	{
		if (ft_strlen(av[i]) == 0)
		{
			ft_dprintf(2, PIPEX_USAGE);
			exit(1);
		}
		i++;
	}
}

int	check_fd(int fd, char *file_name)
{
	if (fd < 0)
		ft_dprintf(2, "pipex: %s: %s\n", strerror(errno), file_name);
	return (fd);
}

int	check_dup2(int fd, char ***commands)
{
	if (fd < 0)
	{
		free_3d_tab(commands);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
