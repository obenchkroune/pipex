/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:26:11 by obenchkr          #+#    #+#             */
/*   Updated: 2023/11/03 23:27:13 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nbr_len(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_result(char *result, int n, size_t buf_size)
{
	size_t	idx;

	if (n == -2147483648)
		ft_strlcpy(result, "-2147483648", buf_size);
	else if (n == 0)
		ft_strlcpy(result, "0", buf_size);
	else
	{
		idx = buf_size - 1;
		result[idx--] = '\0';
		if (n < 0)
			n = -n;
		while (n != 0)
		{
			result[idx--] = n % 10 + '0';
			n /= 10;
		}
		if (idx == 0)
			result[idx] = '-';
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	buf_size;

	buf_size = get_nbr_len(n) + 1;
	result = (char *)malloc(buf_size);
	if (!result)
		return (NULL);
	fill_result(result, n, buf_size);
	return (result);
}
