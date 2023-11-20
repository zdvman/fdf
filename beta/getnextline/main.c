/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:02:31 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/19 23:43:20 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int	main()
{
	int		fd;
	char	*str;

	fd = open("41_with_nl.txt", O_RDONLY);
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
