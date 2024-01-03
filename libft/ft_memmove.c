/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 05:17:01 by obenchkr          #+#    #+#             */
/*   Updated: 2023/11/06 21:48:33 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*udst;
	unsigned char	*usrc;

	if (n == 0)
		return (dst);
	if (!dst && !src)
		return (NULL);
	udst = (unsigned char *)dst;
	usrc = (unsigned char *)src;
	if (dst < src)
		return (ft_memcpy(dst, src, n));
	while (n)
	{
		udst[n - 1] = usrc[n - 1];
		n--;
	}
	return (dst);
}
