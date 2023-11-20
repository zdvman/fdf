/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:18:22 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/20 00:02:16 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

static char *read_from_fd(int fd, char *saved)
{
    char *buf = malloc(BUFFER_SIZE + 1);
    if (!buf)
        return (NULL);

    int chars_read;
    while ((chars_read = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[chars_read] = '\0';
        char *temp = saved;
        saved = ft_strjoin(saved, buf);
        free(temp);

        if (ft_strchr(saved, '\n')) 
            break;
    }

    free(buf); // Освобождение памяти buf

    if (chars_read < 0)
    {
        free(saved);
        return (NULL);
    }

    return saved;
}


static char	*extract_line(char **saved)
{
	char	*new_line_ptr;
	char	*line;
	char	*temp;

	new_line_ptr = ft_strchr(*saved, '\n');
	if (new_line_ptr)
	{
		line = ft_substr(*saved, 0, new_line_ptr - *saved + 1);
		temp = *saved;
		*saved = ft_strdup(new_line_ptr + 1);
		free(temp);
		return (line);
	}
	if (**saved)
	{
		line = ft_strdup(*saved);
		free(*saved);
		*saved = NULL;
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*saved = NULL;
	char	*line;
	
	line = NULL;
	if (fd < 0)
		return (NULL);
	saved = read_from_fd(fd, saved);
	if (!saved)
		return (NULL);
	line = extract_line(&saved);
	return (line);
}
