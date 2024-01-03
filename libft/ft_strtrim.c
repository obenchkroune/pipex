/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:23:09 by obenchkr          #+#    #+#             */
/*   Updated: 2023/11/06 21:43:15 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str, const char *set)
{
	char	*result;
	int		buf_size;

	if (!str)
		return (NULL);
	if (!set)
		return (ft_strdup(str));
	while (*str && ft_strchr(set, *str))
		str++;
	if (*str == '\0')
		return (ft_calloc(sizeof(char), 1));
	buf_size = ft_strlen(str);
	while (*str && ft_strchr(set, str[buf_size - 1]))
		buf_size--;
	result = (char *)ft_calloc(sizeof(char), buf_size + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, buf_size + 1);
	return (result);
}
