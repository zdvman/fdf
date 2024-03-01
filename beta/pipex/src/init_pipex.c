/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:18:26 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/01 22:18:26 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

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

static char	**get_commands(int shift, char **argv, t_pipex *pipex)
{
	char	**cmds;
	int		i;

	i = -1;
	cmds = (char **)malloc(sizeof(char *) * (pipex->num_cmds + 1));
	if (cmds == NULL)
		return (NULL);
	while (++i < pipex->num_cmds)
	{
		cmds[i] = ft_strdup(argv[i + shift]);
		if (cmds[i] == NULL)
		{
			ft_free_array(&cmds);
			return (NULL);
		}
	}
	cmds[i] = NULL;
	return (cmds);
}

static void	validate_cmds(t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->my_cmd = (char ***)malloc(sizeof(char **) * (pipex->num_cmds + 1));
	if (pipex->my_cmd == NULL)
		cleanup(pipex, "malloc error for 3d array of cmd's pointers");
	pipex->my_path = (char **)malloc(sizeof(char *) * (pipex->num_cmds + 1));
	if (pipex->my_path == NULL)
		cleanup(pipex, "malloc error for path array");
	while (++i < pipex->num_cmds)
	{
		pipex->my_cmd[i] = ft_split(pipex->cmds[i], ' ');
		if (!pipex->my_cmd[i])
			cleanup(pipex, "ft_split error in cmd array creation");
		pipex->my_path[i] = get_path(pipex->my_cmd[i][0], pipex->path);
		if (pipex->my_path[i] == NULL)
		{
			write(2, pipex->cmds[i], sizeof(pipex->cmds[i]));
			cleanup(pipex, ": command error");
		}
	}
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	shift;

	pipex->envp = envp;
	if (argc == 6 && ft_strcmp(argv[1], "here_doc") == 0)
	{
		pipex->infile_fd = open_file("temp_file", 0, pipex);
		pipex->outfile_fd = open_file(argv[argc - 1], 2, pipex);
		pipex->num_cmds = argc - 4;
		shift = 3;
	}
	else
	{
		pipex->outfile_fd = open_file(argv[argc - 1], 1, pipex);
		pipex->infile_fd = open_file(argv[1], 0, pipex);
		pipex->num_cmds = argc - 3;
		shift = 2;
	}
	pipex->cmds = get_commands(shift, argv, pipex);
	pipex->path = get_env(envp);
	validate_cmds(pipex);
	create_pipes(pipex, pipex->num_cmds - 1);
	pipex->pid = malloc(sizeof(pid_t) * (argc - 3));
	if (!pipex->pid)
		cleanup(pipex, "pid malloc error");
}
