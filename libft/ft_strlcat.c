/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 05:45:20 by obenchkr          #+#    #+#             */
/*   Updated: 2023/11/06 22:17:07 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	i;
	size_t	j;

	src_size = ft_strlen(src);
	if (n == 0)
		return (src_size);
	dst_size = ft_strlen(dst);
	if (n < dst_size)
		return (n + src_size);
	i = 0;
	j = dst_size;
	while (j < n - 1 && src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (dst_size + src_size);
}
