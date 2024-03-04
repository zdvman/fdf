/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:20:14 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/28 18:31:49 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		write(2, "Arguments Error.\nPlease follow the usage example: ", 50);
		write(2, "./pipex file1 \"cmd1\" \"cmd2\" file2\n", 35);
		return (EXIT_FAILURE);
	}
	t_pipex_zero(&pipex);
	init_pipex(&pipex, argc, argv, envp);
	launch_processes(&pipex);
	cleanup(&pipex, NULL, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
