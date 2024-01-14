/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_av.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:48:14 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/14 23:52:52 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_av(char *cmd)
{
	char	**result;
	int		size;
	int		i;
	int		j;

	size = get_av_size(cmd);
	if (size == -1)
	{
		ft_dprintf(2, "pipex: invalid command: %s\n", cmd);
		exit(EXIT_FAILURE);
	}
	result = malloc((size + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		result[j++] = get_next_av(&cmd[i]);
		i += get_next_idx(&cmd[i]);
	}
	result[j] = NULL;
	return (result);
}
