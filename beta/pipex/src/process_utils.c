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

static void	ft_dup2(t_pipex *pipex, int i)
{
	int	j;

	if (i == 0)
	{
		dup2(pipex->infile_fd, STDIN_FILENO);
		close(pipex->infile_fd);
	}
	else
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
	if (i < pipex->num_cmds - 1)
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
	else
	{
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->outfile_fd);
	}
	j = -1;
	while (++j < pipex->num_pipes)
	{
		close(pipex->pipes[j][0]);
		close(pipex->pipes[j][1]);
	}
}

static void	wait_for_children(t_pipex *pipex)
{
	pid_t	child_pid;
	int		status;
	int		i;

	i = 0;
	while (i < pipex->num_cmds)
	{
		child_pid = waitpid(pipex->pid[i], &status, 0);
		if (child_pid == -1)
			cleanup(pipex, "wait error", EXIT_FAILURE);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			cleanup(pipex, "child process failed", EXIT_FAILURE);
		i++;
	}
}

static void	close_fd_in_parent(t_pipex *pipex, int i)
{
	if (i == 0)
		close(pipex->infile_fd);
	else
	{
		close(pipex->pipes[i - 1][0]);
		close(pipex->pipes[i - 1][1]);
	}
	if (i == pipex->num_cmds - 1)
		close(pipex->outfile_fd);
}

// static void	validate_cmds(t_pipex *pipex, int i)
// {
// 	pipex->my_path = get_path(pipex->my_cmd[i][0], pipex->path);
// 	if (pipex->my_path == NULL)
// 	{
// 		write(2, pipex->my_cmd[i][0], sizeof(pipex->my_cmd[i][0]));
// 		cleanup(pipex, " : command not found", EXIT_FAILURE);
// 	}
// }

void	launch_processes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->num_cmds)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			cleanup(pipex, "fork error", EXIT_FAILURE);
		if (pipex->pid[i] == 0)
		{
			// validate_cmds(pipex, i);
			pipex->my_path = get_path(pipex->my_cmd[i][0], pipex->path);
			ft_dup2(pipex, i);
			execve(pipex->my_path, pipex->my_cmd[i], pipex->envp);
			cleanup(pipex, "execve error", EXIT_FAILURE);
		}
		else
			close_fd_in_parent(pipex, i);
	}
	wait_for_children(pipex);
}
