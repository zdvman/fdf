/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:02:31 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/21 17:15:25 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;

	if (argc < 2)
	{
		printf("Please input name of txt file: %s <name>\n", argv[0]);
		return (1);
        }

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	while((str = get_next_line(fd)))
	{
		printf("%s", str);
		free(str);
	}
	close (fd);
	return (0);
}
