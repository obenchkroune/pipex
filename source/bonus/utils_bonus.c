/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:03:21 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/13 22:17:15 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_2d_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_3d_tab(char ***tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free_2d_tab(tab[i++]);
	free(tab);
}

void	close_pipes(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}
