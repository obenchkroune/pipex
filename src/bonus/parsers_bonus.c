/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:55:00 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/22 12:56:07 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		exit(errno);
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

char	**parse_env_path(char **env)
{
	while (env && *env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (ft_split(*env + 5, ':'));
		env++;
	}
	return (NULL);
}

static char	**combine_exec_argv(char *executable, char **av)
{
	char	**result;
	size_t	buf_size;
	size_t	i;

	buf_size = ft_tabsize(av) + 2;
	result = malloc(sizeof(char *) * buf_size);
	if (!result)
		return (NULL);
	ft_bzero(result, sizeof(char *) * buf_size);
	result[0] = ft_strdup(executable);
	i = 1;
	while (i < buf_size - 1)
	{
		result[i] = ft_strdup(av[i - 1]);
		if (!result[i])
		{
			free_2d_tab(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	***parse_commands(int ac, char **av, char **env)
{
	int		i;
	char	***commands;
	char	**command_av;
	char	*executable;

	commands = malloc(sizeof(char **) * (ac - 2));
	if (!commands)
		exit(errno);
	ft_bzero(commands, sizeof(char **) * (ac - 2));
	i = 0;
	while (i + 3 < ac)
	{
		command_av = get_av(av[i + 2]);
		executable = get_command_executable(command_av[0], env);
		commands[i] = combine_exec_argv(executable, command_av);
		free_2d_tab(command_av);
		free(executable);
		i++;
	}
	commands[i] = NULL;
	return (commands);
}
