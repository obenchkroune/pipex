/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:33:38 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/15 19:44:40 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	handle_executable_error(char **cmd_av, char ***cmds)
{
	ft_dprintf(2, "pipex: command not found: %s\n", cmd_av[0]);
	free_2d_tab(cmd_av);
	free_3d_tab(cmds);
	exit(errno);
}

static void	handle_cmd_error(char ***commands)
{
	ft_dprintf(2, "pipex: %s\n", strerror(errno));
	free(commands);
	exit(errno);
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
		if (!executable)
			handle_executable_error(command_av, commands);
		commands[i] = combine_exec_argv(executable, command_av);
		free_2d_tab(command_av);
		free(executable);
		if (!commands[i])
			handle_cmd_error(commands);
		i++;
	}
	commands[i] = NULL;
	return (commands);
}
