/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:56:45 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/03 01:28:02 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <string.h>

int	ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_fd(int fd, char *path)
{
	if (fd == -1)
		ft_dprintf(2, "%s: %s\n", strerror(errno), path);
	return (fd);
}
