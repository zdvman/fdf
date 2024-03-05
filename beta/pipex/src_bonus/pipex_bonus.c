/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:16:42 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/01 22:16:42 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

static void	get_input(char **argv, t_pipex *pipex)
{
	static char	*saved = NULL;
	char		*line;

	pipex->infile_fd = open_file("temp_file", 1);
	line = get_next_line(0, &saved);
	while (line != NULL)
	{
		if (ft_strncmp(argv[2], line, sizeof(line) - 1) == 0
			&& argv[2][ft_strlen(argv[2])] == '\0'
			&& line[ft_strlen(argv[2])] == '\n'
			&& line[ft_strlen(argv[2]) + 1] == '\0')
		{
			break ;
		}
		ft_putstr_fd(line, pipex->infile_fd);
		free(line);
		line = get_next_line(0, &saved);
	}
	free(line);
	free(saved);
	close(pipex->infile_fd);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		write(2, "Arguments Error.\nPlease follow the usage example: ", 50);
		write(2, "./pipex file1 \"cmd1\" \"cmd2\" ... \"cmdN\" file2\n", 46);
		return (EXIT_FAILURE);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0 && argc >= 6)
		get_input(argv, &pipex);
	t_pipex_zero(&pipex);
	init_pipex(&pipex, argc, argv, envp);
	launch_processes(&pipex);
	cleanup(&pipex, EXIT_SUCCESS);
	unlink("temp_file");
	return (EXIT_SUCCESS);
}
