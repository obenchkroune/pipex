/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:12:43 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/03 01:53:32 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <libft.h>

#define BUFFER_SIZE 100

static void	parse_result(char **line, char *history)
{
	char	*new_line;
	size_t	len;

	if (!history)
	{
		*line = NULL;
		return ;
	}
	new_line = ft_strchr(history, '\n');
	if (!new_line)
	{
		*line = ft_strdup(history);
		return ;
	}
	len = ft_strlen(history) - ft_strlen(new_line) + 1;
	*line = ft_substr(history, 0, len);
}

static void	cleanup_history(char **history)
{
	char	*new_line;
	size_t	buf_size;
	char	*temp;

	if (!*history)
		return ;
	new_line = ft_strchr(*history, '\n');
	if (!new_line)
	{
		free(*history);
		*history = NULL;
		return ;
	}
	buf_size = new_line - ft_strchr(*history, '\0') - 1;
	temp = ft_substr(new_line, 1, buf_size);
	free(*history);
	*history = temp;
}

static int	read_from_fd(int fd, char **history)
{
	char	buffer[BUFFER_SIZE];
	int		bytes;
	char	*temp;

	ft_bzero(buffer, BUFFER_SIZE * sizeof(char));
	bytes = read(fd, buffer, BUFFER_SIZE - 1);
	if (bytes < 0)
		return (bytes);
	buffer[bytes] = '\0';
	temp = *history;
	*history = ft_strjoin(*history, buffer);
	free(temp);
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*history = NULL;
	int			bytes;
	char		*line;

	if (fd < 0)
		return (NULL);
	if (!history)
		history = ft_strdup("");
	bytes = 1;
	while (bytes > 0 && !ft_strchr(history, '\n'))
		bytes = read_from_fd(fd, &history);
	if (!bytes && !ft_strlen(history))
		return (NULL);
	parse_result(&line, history);
	cleanup_history(&history);
	return (line);
}
