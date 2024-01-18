/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:37:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/18 11:58:47 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_executable(char *cmd, char **env)
{
	char	**env_path;
	char	*result;
	int		i;
	
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0)
		return (ft_strdup(cmd));
	result = NULL;
	env_path = parse_env_path(env);
	if (!env_path)
		return (NULL);
	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (env_path[i])
	{
		result = ft_strjoin(env_path[i++], cmd);
		if (access(result, F_OK) == 0)
			break ;
		free(result);
		result = NULL;
	}
	free(cmd);
	free_2d_tab(env_path);
	return (result);
}

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	get_av_size(char *cmd)
{
	int		size;
	int		i;
	char	*next_quote;

	size = 0;
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		size++;
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			next_quote = ft_strchr(&cmd[i + 1], cmd[i]);
			if (!next_quote)
				return (-1);
			i = next_quote - cmd + 1;
		}
		else
			while (cmd[i] && !ft_isspace(cmd[i]))
				i++;
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
	}
	return (size);
}

int	get_next_idx(char *cmd)
{
	int		i;
	char	*next_quote;

	i = 0;
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '"' || cmd[i] == '\'')
	{
		next_quote = ft_strchr(&cmd[i + 1], cmd[i]);
		return (next_quote - cmd + 1);
	}
	else
	{
		while (cmd[i] && !ft_isspace(cmd[i]))
			i++;
	}
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;
	return (i);
}

char	*get_next_av(char *cmd)
{
	int		size;
	int		i;
	int		temp;
	char	*next_quote;

	i = 0;
	size = 0;
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '"' || cmd[i] == '\'')
	{
		next_quote = ft_strchr(&cmd[i + 1], cmd[i]);
		if (!next_quote)
			return (NULL);
		return (ft_substr(cmd, i + 1, next_quote - cmd - 1));
	}
	temp = i;
	while (cmd[i] && !ft_isspace(cmd[i]))
		i++;
	size = i - temp;
	return (ft_substr(cmd, temp, size));
}
