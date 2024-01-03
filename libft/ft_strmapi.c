/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:29:49 by obenchkr          #+#    #+#             */
/*   Updated: 2023/11/03 23:33:42 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	i;

	result = (char *)malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		result[i] = (*f)(i, *s);
		i++;
		s++;
	}
	result[i] = '\0';
	return (result);
}
