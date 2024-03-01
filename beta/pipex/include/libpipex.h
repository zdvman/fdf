/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:10:17 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/29 16:09:08 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPIPEX_H
# define LIBPIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		num_cmds;
	int		num_pipes;
	int		**pipes;
	pid_t	*pid;
	char	**cmds;
	char	**envp;
	char	*path;
}				t_pipex;

// Прототипы функций
int		open_file(char *file, int flag, t_pipex *pipex);
void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void	ft_free_array(char ***array);
void	cleanup(t_pipex *pipex, char *error_msg);
void	launch_processes(t_pipex *pipex);
char	*get_env(char **envp);
char	*get_path(char *cmd, char *path);

#endif
