/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:18:38 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/05 19:21:47 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

static int	cmd_validation(t_pipex *pipex, int i)
{
	int	not_valid_flag;

	not_valid_flag = 0;
	pipex->my_path = get_path(pipex->my_cmd[i][0], pipex->path);
	if ((access(pipex->my_path, X_OK) != 0
			|| access(pipex->my_path, F_OK) != 0)
		&& (pipex->infile_fd > 0 || i > 0))
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putstr_fd(pipex->my_cmd[i][0], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		not_valid_flag = 1;
	}
	return (not_valid_flag);
}

int	input_validation(t_pipex *pipex, int i)
{
	int	not_valid_flag;

	not_valid_flag = 0;
	if (pipex->infile_fd < 0)
		not_valid_flag = 1;
	if (i == pipex->num_cmds - 1)
	{
		if (pipex->flag_here_doc == 1)
			pipex->outfile_fd = open_file(pipex->outfile_name, 2);
		else
			pipex->outfile_fd = open_file(pipex->outfile_name, 1);
		if (pipex->outfile_fd < 0)
		{
			not_valid_flag = 1;
			return (not_valid_flag);
		}
	}
	not_valid_flag = cmd_validation(pipex, i);
	return (not_valid_flag);
}
