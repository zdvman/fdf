/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:18:22 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/14 21:17:14 by dzuiev           ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	t_list			*tmp;
	char			buf[BUFFER_SIZE + 1];
	char			*next_line;
	int				chars_read;
	int				next_line_len;

	next_line_len = 0;
	chars_read = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (NULL);
	// Create linked list from file with fd file descriptor
	// each node is of BUFFER_SIZE or less if '\n' is found
	// or EOF is reached
	while ((chars_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[chars_read] = '\0';
    	ft_lstadd_back(&list, ft_lstnew(strdup(buf)));
    	next_line_len += chars_read;
    	if (ft_strchr(buf, '\n'))
        	break;
	}
	// Create a string from linked list
	next_line = (char *)ft_calloc(next_line_len + 1, 1);
	// printf("next_line_len : %i\n", next_line_len);
	// printf("buf			  : %s\n", buf);
	// printf("list size	  : %i\n", ft_lstsize(list));

	tmp = list;
	while (tmp)
	{
		// printf("list->content : %s\n", (char *)tmp->content);
		ft_strlcat(next_line, tmp->content, next_line_len + 1);
		tmp = tmp->next;
	}
	return (next_line);
}
