/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:49:12 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/01 15:22:58 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

static void	close_fd(t_pipex *pipex, int i)
{
	int	j;

	j = 0;
	while (j < pipex->num_pipes)
	{
		if (pipex->pipes[j][0] >= 0)
			close(pipex->pipes[j][0]);
		if (pipex->pipes[j][1] >= 0)
			close(pipex->pipes[j][1]);
		j++;
	}
	if (i == 0)
	{
		if (pipex->infile_fd >= 0)
			close(pipex->infile_fd);
	}
	if (i == pipex->num_cmds - 1)
	{
		if (pipex->outfile_fd >= 0)
			close(pipex->outfile_fd);
	}
}

static void	ft_dup2(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
			cleanup(pipex, EXIT_FAILURE);
	}
	else
	{
		if (dup2(pipex->pipes[i - 1][0], STDIN_FILENO) == -1)
			cleanup(pipex, EXIT_FAILURE);
	}
	if (i < pipex->num_cmds - 1)
	{
		if (dup2(pipex->pipes[i][1], STDOUT_FILENO) == -1)
			cleanup(pipex, EXIT_FAILURE);
	}
	else
	{
		if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
			cleanup(pipex, EXIT_FAILURE);
	}
	close_fd(pipex, i);
}

static void	wait_for_children(t_pipex *pipex)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = 0;
	i = -1;
	while (++i < pipex->num_cmds)
	{
		waitpid(pipex->pid[i], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_status = WEXITSTATUS(status);
	}
	if (exit_status != 0)
		cleanup(pipex, exit_status);
}

static void	close_fd_in_parent(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		if (pipex->infile_fd >= 0)
			close(pipex->infile_fd);
	}
	else
	{
		if (pipex->pipes[i - 1][0] >= 0)
			close(pipex->pipes[i - 1][0]);
		if (pipex->pipes[i - 1][1] >= 0)
			close(pipex->pipes[i - 1][1]);
	}
	if (i == pipex->num_cmds - 1)
	{
		if (pipex->outfile_fd >= 0)
			close(pipex->outfile_fd);
	}
}

void	launch_processes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->num_cmds)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			cleanup(pipex, EXIT_FAILURE);
		if (pipex->pid[i] == 0)
		{
			if (input_validation(pipex, i) == 1)
				cleanup(pipex, EXIT_FAILURE);
			ft_dup2(pipex, i);
			execve(pipex->my_path, pipex->my_cmd[i], pipex->envp);
			cleanup(pipex, EXIT_FAILURE);
		}
		else
			close_fd_in_parent(pipex, i);
	}
	wait_for_children(pipex);
}
