/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:10:17 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/04 18:54:44 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPIPEX_H
# define LIBPIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		temp_fd;
	int		num_cmds;
	int		num_pipes;
	int		**pipes;
	pid_t	*pid;
	char	**cmds;
	char	***my_cmd;
	char	**envp;
	char	*my_path;
	char	*path;
}				t_pipex;

int		open_file(char *file, int flag, t_pipex *pipex);
void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void	ft_free_array(char ***array);
void	ft_free_3d_array(char ****array);
void	cleanup(t_pipex *pipex, char *error_msg, int exit_status);
void	ft_clean_pipes(int ***pipes, int num_pipes);
void	launch_processes(t_pipex *pipex);
void	t_pipex_zero(t_pipex *pipex);
pid_t	*allocate_pid(t_pipex *pipex);
char	*get_env(char **envp);
char	*get_path(char *cmd, char *path);

#endif
