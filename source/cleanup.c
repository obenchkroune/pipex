/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 04:38:49 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/03 04:43:30 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2d_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_3d_array(char ***arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free_2d_array(arr[i]);
		i++;
	}
	free(arr);
}

void	cleanup_pipex(t_pipex *pipex)
{
	free_2d_array(pipex->cmds_path);
	free_2d_array(pipex->env_path);
	free_3d_array(pipex->commands);
	free(pipex);
}
