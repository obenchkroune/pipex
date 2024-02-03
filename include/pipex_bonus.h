/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:54:16 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/03 01:46:48 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H

# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_command
{
	char	*executable;
	char	**argv;
}	t_command;

typedef struct s_pipeline
{
	int	pipe_fd[2];
	int	input_fd;
	int	output_fd;
}	t_pipeline;

t_command	**parse_commands(int ac, char **av, char **env);
void		cleanup_commands(t_command **commands);
char		*get_cmd_exec(char *cmd, char **env);
int			get_av_size(char *cmd);
int			get_next_idx(char *cmd);
char		*get_next_av(char *cmd);
char		**get_av(char *cmd);
void		free_2d_tab(char **tab);
void		free_3d_tab(char ***tab);
void		ft_dprintf(int fd, const char *format, ...);
int			ft_tabsize(char **tab);
char		**parse_env_path(char **env);
int			check_fd(int fd, char *path);
void		ft_error(t_command **commands);
int			pipeline(int in_fd, int out_fd, t_command **commands, char **env);
void		check_errors(char **av, int ac);
int			get_here_doc_fd(char *limiter);
char		*get_next_line(int fd);

#endif
