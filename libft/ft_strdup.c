/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 07:28:30 by obenchkr          #+#    #+#             */
/*   Updated: 2023/11/03 07:32:00 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*result;
	size_t	buf_size;

	buf_size = ft_strlen(str) + 1;
	result = (char *)malloc(buf_size);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, buf_size);
	return (result);
}
