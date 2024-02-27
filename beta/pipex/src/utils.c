/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:46:16 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/27 13:46:16 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

static void	ft_clean_pipes(int ***pipes, int num_pipes)
{
	int	i;

	if (!*pipes)
		return ;
	i = 0;
	while (i < num_pipes)
	{
		if ((*pipes)[i])
		{
			close((*pipes)[i][0]);
			close((*pipes)[i][1]);
			free((*pipes)[i]);
		}
		i++;
	}
	free(*pipes);
	*pipes = NULL;
}

static void	create_pipes(t_pipex *pipex, int num_pipes)
{
	pipex->pipes = (int **)malloc(sizeof(int *) * num_pipes);
	if (!pipex->pipes)
		cleanup(pipex, "malloc error");
	pipex->num_pipes = 0;
	while (pipex->num_pipes < num_pipes)
	{
		pipex->pipes[pipex->num_pipes] = malloc(2 * sizeof(int));
		if (pipex->pipes[pipex->num_pipes] == NULL
			|| pipe(pipex->pipes[pipex->num_pipes]) == -1)
			cleanup(pipex, "pipe/malloc error");
		pipex->num_pipes++;
	}
}

int	open_file(char *file, int flag, t_pipex *pipex)
{
	int	fd;

	if (flag == 0)
		fd = open(file, O_RDONLY, 0644);
	else if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		cleanup(pipex, "open file error");
	return (fd);
}

void	cleanup(t_pipex *pipex, char *error_msg)
{
	if (pipex->infile_fd >= 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd >= 0)
		close(pipex->outfile_fd);
	if (pipex->path)
		free(pipex->path);
	if (pipex->pipes)
		ft_clean_pipes(&(pipex->pipes), pipex->num_pipes);
	if (error_msg)
	{
		perror(error_msg);
		exit(EXIT_FAILURE);
	}
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->infile_fd = open_file(argv[1], 0, pipex);
	pipex->outfile_fd = open_file(argv[argc - 1], 1, pipex);
	pipex->num_cmds = argc - 3;
	pipex->cmds = argv + 2;
	pipex->envp = envp;
	pipex->path = get_env(envp);
	create_pipes(pipex, argc - 4);
}
