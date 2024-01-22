/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:53:16 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/22 12:44:18 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_pipeline
{
	int	pipe_fd[2];
	int	input_fd;
	int	output_fd;
}	t_pipeline;

char	***parse_commands(int ac, char **av, char **env);
char	*get_command_executable(char *cmd, char **env);
int		get_av_size(char *cmd);
int		get_next_idx(char *cmd);
char	*get_next_av(char *cmd);
char	**get_av(char *cmd);
void	free_2d_tab(char **tab);
void	free_3d_tab(char ***tab);
void	ft_dprintf(int fd, const char *format, ...);
int		ft_tabsize(char **tab);
char	**parse_env_path(char **env);
int		check_fd(int fd, char *path);
void	ft_error(char *s, char ***commands);
int		pipeline(int in_fd, int out_fd, char ***commands, char **env);
void	check_errors(int ac, char **av);

#endif