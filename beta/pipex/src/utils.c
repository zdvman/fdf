/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:46:16 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/04 14:51:58 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

void	ft_clean_pipes(int ***pipes, int num_pipes)
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

void	ft_free_3d_array(char ****array)
{
	int	i;
	int	j;

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

void	cleanup(t_pipex *pipex, int exit_status)
{
	if (pipex->cmds)
		ft_free_array(&(pipex->cmds));
	if (pipex->my_cmd)
		ft_free_3d_array(&(pipex->my_cmd));
	if (pipex->pid)
	{
		free(pipex->pid);
		pipex->pid = NULL;
	}
	if (pipex->infile_fd >= 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd >= 0)
		close(pipex->outfile_fd);
	if (pipex->my_path)
	{
		free(pipex->my_path);
		pipex->my_path = NULL;
	}
	if (pipex->pipes)
		ft_clean_pipes(&(pipex->pipes), pipex->num_pipes);
	if (exit_status)
		exit(exit_status);
}

pid_t	*allocate_pid(t_pipex *pipex)
{
	pid_t	*pid;

	pid = (pid_t *)malloc(sizeof(pid_t) * pipex->num_cmds);
	if (pid == NULL)
	{
		ft_putstr_fd("malloc error for pid array\n", STDERR_FILENO);
		cleanup(pipex, EXIT_FAILURE);
	}
	return (pid);
}

int	open_file(char *file, int flag)
{
	int	fd;

	if (flag == 0)
		fd = open(file, O_RDONLY, 0644);
	else if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (flag == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (fd);
}
