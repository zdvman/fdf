/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:18:22 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/16 01:19:42 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <fcntl.h>
#include "get_next_line.h"

// void	print_list(t_list *list)
// {
// 	int	i;

// 	i = 0;
// 	while (list)
// 	{
// 		i++;
// 		printf(" node [%i] : %s", i, (char *)list->content);
// 		list = list->next;
// 	}
// }

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	char			*next_line = NULL;
	char			*nextline_index;
	int				chars_read;
	size_t			nextline_len;
	char			*temp;

	nextline_len = 0;
	chars_read = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (NULL);
	 while((chars_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[chars_read] = '\0';
		nextline_index = ft_strchr(buf, '\n');
		if (nextline_index != NULL)
		{
			// nextline_len += nextline_index - buf + 1;
			temp = realloc(next_line, nextline_len + (nextline_index - buf) + 2);
			if (!temp)
			{
				free(next_line);
				return (NULL);
			}
			next_line = temp;
			ft_memcpy(next_line + nextline_len, buf, nextline_index - buf + 1);
			next_line[nextline_len + (nextline_index - buf) + 1] = '\0';
			return (next_line);
		}
		temp = realloc(next_line, nextline_len + chars_read + 1);
		if (!temp)
		{
			free(next_line);
			return (NULL);
		}
		next_line = temp;
		ft_memcpy(next_line + nextline_len, buf, chars_read);
		nextline_len += chars_read;
		next_line[nextline_len] = '\0';
	}
	return (next_line);
}
