/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:46:16 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/01 18:12:08 by dzuiev           ###   ########.fr       */
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
	else if (flag == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		cleanup(pipex, "open file error");
	return (fd);
}

void    ft_free_3d_array(char ****array) 
{
    int i;
    int j;

    if (array == NULL || *array == NULL)
        return ;
    i = 0;
    while ((*array)[i])
    {
        j = 0;
        while ((*array)[i][j])
        {
            free((*array)[i][j]);
            j++;
        }
        free((*array)[i]);
        i++;
    }
    free(*array);
    *array = NULL;
}

void	cleanup(t_pipex *pipex, char *error_msg)
{
    if (pipex->cmds)
        ft_free_array(&(pipex->cmds));
    if (pipex->my_cmd)
        ft_free_3d_array(&(pipex->my_cmd));
	if (pipex->pid)
		free(pipex->pid);
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

char **get_commands(int shift, char **argv, t_pipex *pipex)
{
    char    **cmds;
    int     i;

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

void validate_cmds(t_pipex *pipex)
{
    int i;

    i = -1;
    pipex->my_cmd = (char ***)malloc(sizeof(char **) * (pipex->num_cmds + 1));
    if (pipex->my_cmd == NULL)
        cleanup(pipex, "malloc error for 3d array of cmd's pointers");
    while (++i < pipex->num_cmds)
    {
	    pipex->my_cmd[i] = ft_split(pipex->cmds[i], ' ');
	    if (!pipex->my_cmd[i])
	        cleanup(pipex, "ft_split error in cmd array creation");
	    pipex->my_path[i] = get_path(pipex->my_cmd[i][0], pipex->path);
	    if (pipex->my_path[i] == NULL)
        {
            perror(pipex->cmds[i]);
    	    cleanup(pipex, " :command error");
        }
    }
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
    int shift;

	pipex->pid = malloc(sizeof(pid_t) * (argc - 3));
	if (!pipex->pid)
		cleanup(pipex, "pid malloc error");
	pipex->infile_fd = open_file(argv[1], 0, pipex);
	pipex->outfile_fd = open_file(argv[argc - 1], 1, pipex);
    if (argc == 6 && ft_strcmp(argv[1], "here_doc") == 0)
    {
        pipex->num_cmds = argc - 4;
        shift = 3;
    }
    else
    {
	    pipex->num_cmds = argc - 3;
        shift = 2;
    }
	pipex->cmds = get_commands(shift, argv, pipex);
    validate_cmds(pipex);
	pipex->envp = envp;
	pipex->path = get_env(envp);
	create_pipes(pipex, argc - 4);
}
