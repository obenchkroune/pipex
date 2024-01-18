/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:27:49 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/18 11:39:53 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# define PIPEX_USAGE "pipex: usage: ./pipex [infile] [cmd1] [cmd2] [outfile]\n"

# include "libft.h"
# include <stdarg.h>
# include <sys/wait.h>
# include <sys/fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_pipeline
{
	int	pipe_fds[2];
	int	fd;
}	t_pipeline;

void	check_errors(int ac, char **av);
void	close_pipes(int fd[2]);
void	pipeline(char ***commands, char **env);
void	ft_dprintf(int fd, const char *format, ...);
int		check_fd(int fd, char *file_name);
char	**parse_env_path(char **env);
char	***parse_commands(int ac, char **av, char **env);
char	*get_command_executable(char *cmd, char **env);
size_t	ft_tabsize(char **tab);
void	free_2d_tab(char **tab);
void	free_3d_tab(char ***tab);
char	**get_av(char *cmd);
char	*get_next_av(char *cmd);
int		get_next_idx(char *cmd);
int		get_av_size(char *cmd);
int		check_dup2(int fd, char ***commands);

#endif