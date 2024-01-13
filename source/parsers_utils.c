/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:37:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/13 20:27:17 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_executable(char *cmd, char **env)
{
	char	**env_path;
	char	*result;
	int		i;

	result = NULL;
	env_path = parse_env_path(env);
	if (!env_path)
		return (NULL);
	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (env_path[i])
	{
		result = ft_strjoin(env_path[i++], cmd);
		if (access(result, X_OK | F_OK) == 0)
			break ;
		free(result);
		result = NULL;
	}
	free(cmd);
	free_2d_tab(env_path);
	return (result);
}
