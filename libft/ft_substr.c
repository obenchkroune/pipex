/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:02:43 by obenchkr          #+#    #+#             */
/*   Updated: 2023/11/04 02:19:29 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	size;

	if (!str)
		return (NULL);
	if (start >= ft_strlen(str))
		return (ft_strdup(""));
	size = ft_strlen(str + start);
	if (len > size)
		len = size;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, &str[start], len + 1);
	return (result);
}
