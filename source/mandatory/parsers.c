/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 04:37:12 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/06 01:52:56 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_executables(char ***commands, t_pipex *pipex)
{
	char	**bin_paths;
	size_t	size;
	size_t	i;

	size = 0;
	while (commands[size] != NULL)
		size++;
	bin_paths = malloc(sizeof(char **) * (size + 1));
	if (!bin_paths)
		return (NULL);
	i = 0;
	while (i < size)
	{
		bin_paths[i] = get_exec_path(commands[i][0], pipex);
		i++;
	}
	bin_paths[i] = NULL;
	return (bin_paths);
}

char	***parse_commands(int ac, char **av)
{
	size_t	i;
	size_t	j;
	char	***commands;

	commands = malloc(sizeof(char **) * ac - 1);
	if (!commands)
		return (NULL);
	i = 2;
	j = 0;
	while (i < (size_t)ac - 1)
	{
		commands[j++] = ft_split(av[i], ' ');
		i++;
	}
	commands[j] = NULL;
	return (commands);
}

char	**parse_path(char **envp)
{
	while (envp != NULL && *envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}
