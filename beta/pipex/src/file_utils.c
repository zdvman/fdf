/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:59:00 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/19 19:59:00 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

int	open_file(char *file, int flag, t_pipex *pipex)
{
	int	fd;

	if (flag == 0)
		fd = open(file, O_RDONLY, 0644);
	else if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		cleanup(pipex);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
