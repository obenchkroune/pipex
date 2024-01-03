/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 03:30:52 by obenchkr          #+#    #+#             */
/*   Updated: 2024/01/03 05:33:49 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "libft.h"
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

# define PIPEX_USAGE "pipex: usage: ./pipex [file1] [cmd1] [file2] [cmd2]."
# define PIPEX_NO_CMD "command not found: "

typedef struct s_pipex
{
	char	**envp;
	char	**env_path;
	char	***commands;
	char	**cmds_path;
	int		pipe_fds[2];
	int		fdd;
	char	*in_file;
	char	*out_file;
}	t_pipex;

void	init_pipex(t_pipex **data, int ac, char **av, char **envp);
char	*get_bin_path(char *cmd, t_pipex *pipex);
char	**parse_path(char **envp);
char	***parse_commands(int ac, char **av);
char	**parse_binaries(char ***commands, t_pipex *pipex);
void	cleanup_pipex(t_pipex *pipex);
void	pipeline(t_pipex *pipex);
void	ft_put_error(char *str, char *str2);
void	ft_put_errno(char *str);
void	clean_exit(t_pipex *pipex);

#endif