/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 05:03:26 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/06 01:59:08 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_put_errno(char *str)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

void	ft_put_error(char *str, char *str2)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (!str2)
		ft_putstr_fd("\n", STDERR_FILENO);
	else
		ft_putendl_fd(str2, STDERR_FILENO);
}

void	clean_exit(t_pipex *pipex)
{
	cleanup_pipex(pipex);
	exit(EXIT_FAILURE);
}
