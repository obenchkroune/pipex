/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:35:10 by obenchkr          #+#    #+#             */
/*   Updated: 2023/11/06 21:45:24 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *str, char c)
{
	size_t	count;
	int		is_word;

	count = 0;
	is_word = 0;
	while (*str)
	{
		if (!is_word && *str != c)
		{
			count++;
			is_word = 1;
		}
		if (is_word && *str == c)
		{
			is_word = 0;
		}
		str++;
	}
	return (count);
}

static char	*get_next_word(const char *str, char c, size_t *offset)
{
	size_t	length;
	size_t	idx;
	size_t	start;

	length = 0;
	idx = *offset;
	while (str[idx] && str[idx] == c)
		idx++;
	start = idx;
	while (str[idx] && str[idx] != c)
	{
		length++;
		idx++;
	}
	*offset = start + length + 1;
	return (ft_substr(str, start, length));
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	words_count;
	size_t	i;
	size_t	offset;

	words_count = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	offset = 0;
	while (i < words_count)
	{
		result[i] = get_next_word(s, c, &offset);
		i++;
	}
	result[i] = NULL;
	return (result);
}
