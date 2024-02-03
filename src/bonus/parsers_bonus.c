/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:55:00 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/03 01:49:41 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <libft.h>
#include <errno.h>
#include <stdlib.h>

char	**get_av(char *cmd)
{
	char	**result;
	int		size;
	int		i;
	int		j;

	size = get_av_size(cmd);
	if (size == -1)
	{
		ft_dprintf(2, "invalid command: %s\n", cmd);
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

t_command	**parse_commands(int ac, char **av, char **env)
{
	int			i;
	t_command	**commands;

	commands = malloc(sizeof(t_command *) * (ac - 2));
	if (!commands)
		exit(errno);
	ft_bzero(commands, sizeof(t_command *) * (ac - 2));
	i = 0;
	while (i + 3 < ac)
	{
		commands[i] = malloc(sizeof(t_command));
		if (!commands[i])
			ft_error(commands);
		commands[i]->argv = get_av(av[i + 2]);
		commands[i]->executable = get_cmd_exec(commands[i]->argv[0], env);
		i++;
	}
	commands[i] = NULL;
	return (commands);
}
