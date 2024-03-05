/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:18:26 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/04 15:41:05 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

static void	create_pipes(t_pipex *pipex, int num_pipes)
{
	pipex->pipes = (int **)malloc(sizeof(int *) * num_pipes);
	if (!pipex->pipes)
	{
		ft_putstr_fd("malloc error\n", 2);
		cleanup(pipex, EXIT_FAILURE);
	}
	pipex->num_pipes = 0;
	while (pipex->num_pipes < num_pipes)
	{
		pipex->pipes[pipex->num_pipes] = malloc(2 * sizeof(int));
		if (pipex->pipes[pipex->num_pipes] == NULL
			|| pipe(pipex->pipes[pipex->num_pipes]) == -1)
		{
			ft_putstr_fd("pipe/malloc error\n", 2);
			cleanup(pipex, EXIT_FAILURE);
		}
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

char	***get_my_cmd(t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->my_cmd = (char ***)malloc(sizeof(char **) * (pipex->num_cmds + 1));
	if (pipex->my_cmd == NULL)
	{
		ft_putstr_fd("malloc error for 3d array of cmd's pointers\n", 2);
		cleanup(pipex, EXIT_FAILURE);
	}
	while (++i < pipex->num_cmds)
	{
		pipex->my_cmd[i] = ft_split(pipex->cmds[i], ' ');
		if (!pipex->my_cmd[i])
		{
			ft_putstr_fd("ft_split error in cmd array creation\n", 2);
			cleanup(pipex, EXIT_FAILURE);
		}
	}
	pipex->my_cmd[i] = NULL;
	return (pipex->my_cmd);
}

void	t_pipex_zero(t_pipex *pipex)
{
	pipex->flag_here_doc = 0;
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->num_cmds = 0;
	pipex->num_pipes = 0;
	pipex->pipes = NULL;
	pipex->pid = NULL;
	pipex->cmds = NULL;
	pipex->my_cmd = NULL;
	pipex->my_path = NULL;
	pipex->envp = NULL;
	pipex->path = NULL;
	pipex->outfile_name = NULL;
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	shift;

	pipex->envp = envp;
	pipex->path = get_env(envp);
	if (argc >= 6 && ft_strcmp(argv[1], "here_doc") == 0)
	{
		pipex->flag_here_doc = 1;
		pipex->infile_fd = open_file("temp_file", 0);
		pipex->outfile_name = argv[argc - 1];
		pipex->num_cmds = argc - 4;
		shift = 3;
	}
	else
	{
		pipex->infile_fd = open_file(argv[1], 0);
		pipex->outfile_name = argv[argc - 1];
		pipex->num_cmds = argc - 3;
		shift = 2;
	}
	pipex->cmds = get_commands(shift, argv, pipex);
	pipex->my_cmd = get_my_cmd(pipex);
	pipex->pid = allocate_pid(pipex);
	create_pipes(pipex, pipex->num_cmds - 1);
}
