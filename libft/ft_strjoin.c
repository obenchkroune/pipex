/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:14:26 by obenchkr          #+#    #+#             */
/*   Updated: 2023/11/06 21:08:48 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	buf_size;

	if (!s1 || !s2)
		return (NULL);
	buf_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(buf_size);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, buf_size);
	ft_strlcat(result, s2, buf_size);
	return (result);
}
