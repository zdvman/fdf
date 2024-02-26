/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:20:14 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/16 12:20:14 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

void child_process(int i, t_pipex *pipex, int in, int out)
{
	char	**cmd;
	char	*my_path;

	if (i > 0)
		dup2(in, 0);
	if (i < pipex->num_cmds - 1)
		dup2(out, 1);
	close_unused_pipes(pipex, i);
	cmd = ft_split(pipex->cmds[i], ' ');
	if (!cmd)
	{
		perror("ft_split");
		cleanup(pipex);
		exit(EXIT_FAILURE);
	}
	my_path = get_path(cmd[0], pipex->path);
	execve(my_path, cmd, pipex->envp);
	perror("execve");
	cleanup(pipex);
	exit(EXIT_FAILURE);
}

void launch_processes(t_pipex *pipex)
{
	pid_t	pid;
	int		i;
	int		in;
	int		out;

	i = -1;
	in = pipex->infile_fd;
	while (++i < pipex->num_cmds)
	{
		if (i < pipex->num_cmds - 1)
			out = pipex->pipes[i][1];
		else
			out = pipex->outfile_fd;
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			cleanup(pipex);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			child_process(i, pipex, in, out);
		close_unused_pipes(pipex, i);
		in = pipex->pipes[i][0];
	}
}

void	close_unused_pipes(t_pipex *pipex, int i)
{
	int j;

	j = 0;
	while (j < pipex->num_pipes)
	{
		if (j != i)
		{
			if (pipex->pipes[j][0] >= 0)
				close(pipex->pipes[j][0]);
			if (pipex->pipes[j][1] >= 0)
				close(pipex->pipes[j][1]);
		}
		j++;
	}
}

void wait_for_children(t_pipex *pipex)
{
	int	status;
	int	i;

	i = 0;
	while (i < pipex->num_cmds)
	{
		wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			cleanup(pipex);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_pipex(t_pipex *pipex)
{
	launch_processes(pipex);
	wait_for_children(pipex);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		write(2, "Arguments Error.\nPlease follow the usage example: ./pipex infile \"cmd1\" \"cmd2\" ... \"cmdN\" outfile\n", 99);
		return (EXIT_FAILURE);
	}
	init_pipex(&pipex, argc, argv, envp);
	ft_pipex(&pipex);
	cleanup(&pipex);
	return (EXIT_SUCCESS);
}
