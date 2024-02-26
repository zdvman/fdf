/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:05:12 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/19 18:05:12 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

void ft_clean_pipes(int ***pipes, int num_pipes)
{
	int i;

	if (*pipes == NULL)
		return ;
	i = 0;
	while (i < num_pipes)
	{
		if ((*pipes)[i])
		{
			if ((*pipes)[i][0] >= 0)
				close((*pipes)[i][0]);
			if ((*pipes)[i][1] >= 0)
				close((*pipes)[i][1]);
			free((*pipes)[i]);
		}
		i++;
	}
	free(*pipes);
	*pipes = NULL;
}


void cleanup(t_pipex *pipex)
{
	if (pipex->infile_fd >= 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd >= 0)
		close(pipex->outfile_fd);
	if (pipex->cmds)
		ft_free_array(&(pipex->cmds));
	if (pipex->path)
		free(pipex->path);
	if (pipex->pipes)
		ft_clean_pipes(&(pipex->pipes), pipex->num_pipes);
}

void	create_pipes(t_pipex *pipex, int num_pipes)
{
	pipex->pipes = (int **)malloc(sizeof(int *) * num_pipes);
	if (!pipex->pipes)
	{
		perror("malloc");
		cleanup(pipex);
		exit(EXIT_FAILURE);
	}
	pipex->num_pipes = 0;
	while (pipex->num_pipes < num_pipes)
	{
		pipex->pipes[pipex->num_pipes] = malloc(2 * sizeof(int));
		if (pipex->pipes[pipex->num_pipes] == NULL || pipe(pipex->pipes[pipex->num_pipes]) == -1)
		{
			perror("pipe/malloc");
			cleanup(pipex);
			exit(EXIT_FAILURE);
		}
		pipex->num_pipes++;
	}
}

void init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->infile_fd = open_file(argv[1], 0, pipex);
	pipex->outfile_fd = open_file(argv[argc - 1], 1, pipex);
	pipex->num_cmds = argc - 3;
	pipex->cmds = argv + 2;
	pipex->envp = envp;
	pipex->path = get_env(envp);
	create_pipes(pipex, argc - 4);
}
