/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:53:38 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/13 22:16:58 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1) == 's')
		{
			ft_putstr_fd(va_arg(args, char *), fd);
			format += 2;
		}
		else
		{
			ft_putchar_fd(*format, fd);
			format++;
		}
	}
	va_end(args);
}
