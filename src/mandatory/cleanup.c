/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:59:58 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/03 00:35:25 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

void	cleanup_commands(t_command **commands)
{
	int	i;

	i = 0;
	while (commands && commands[i])
	{
		free(commands[i]->executable);
		free_2d_tab(commands[i]->argv);
		free(commands[i]);
		i++;
	}
	free(commands);
}

void	free_2d_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_3d_tab(char ***tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free_2d_tab(tab[i++]);
	}
	free(tab);
}
