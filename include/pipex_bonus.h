/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:11:29 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/16 22:10:05 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H

# define PIPEX_BONUS_USAGE \
"pipex: usage: ./pipex [infile] [cmd1] [cmd2] ... [cmdn] [outfile]\n"

# define PIPEX_HERE_DOC_USAGE \
"pipex: usage: ./pipex here_doc [LIMITER] [cmd1] [cmd2] [outfile]\n"

# include "libft.h"
# include <sys/wait.h>
# include <sys/fcntl.h>
# include <stdarg.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_pipeline
{
	int	pipe_fds[2];
	int	fd;
}	t_pipeline;

int		check_dup2(int fd, char ***commands);
char	*get_next_line(int fd);
void	close_pipes(int fd[2]);
void	check_errors(int ac, char **av);
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

#endif