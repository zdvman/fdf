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

void	child_process(int i, t_pipex *pipex, int in, int out)
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
		cleanup(pipex, "ft_split error");
	my_path = get_path(cmd[0], pipex->path);
	execve(my_path, cmd, pipex->envp);
	cleanup(pipex, "execve error");
}

void	launch_processes(t_pipex *pipex)
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
			cleanup(pipex, "fork error");
		if (pid == 0)
			child_process(i, pipex, in, out);
		if (i > 0)
			close(in);
		if (i < pipex->num_cmds - 1)
			close(out);
		in = pipex->pipes[i][0];
	}
}

void	close_unused_pipes(t_pipex *pipex, int current_pipe)
{
	int	j;

	j = -1;
	while (++j < pipex->num_pipes)
	{
		if (j != current_pipe)
		{
			close(pipex->pipes[j][0]);
			close(pipex->pipes[j][1]);
		}
	}
}

void	wait_for_children(t_pipex *pipex)
{
	pid_t	child_pid;
	int		status;
	int		i;

	i = 0;
	while (i < pipex->num_cmds)
	{
		child_pid = wait(&status);
		if (child_pid == -1)
			cleanup(pipex, "wait error");
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			cleanup(pipex, "child process failed");
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		write(2, "Arguments Error.\nPlease follow the usage example: ", 50);
		write(2, "./pipex infile \"cmd1\" \"cmd2\" ... \"cmdN\" outfile\n", 49);
		return (EXIT_FAILURE);
	}
	init_pipex(&pipex, argc, argv, envp);
	launch_processes(&pipex);
	wait_for_children(&pipex);
	cleanup(&pipex, NULL);
	return (EXIT_SUCCESS);
}
