/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:18:22 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/20 17:10:26 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	n;

	n = 0;
	while (size > 1 && *src != '\0')
	{
		*dest++ = *src++;
		n++;
		size--;
	}
	if (size > 0)
		*dest = '\0';
	return (n + ft_strlen(src));
}

char	*ft_strdup(const char *str)
{
	char	*dup;
	int		i;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*read_from_fd(int fd, char *saved)
{
	int		chars_read;
	char	*buf;
	char	*temp;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	chars_read = read(fd, buf, BUFFER_SIZE);
	while (chars_read > 0)
	{
		buf[chars_read] = '\0';
		temp = saved;
		saved = ft_strjoin(saved, buf);
		free(temp);
		if (ft_strchr(saved, '\n'))
			break ;
		chars_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (chars_read < 0)
	{
		free(saved);
		return (NULL);
	}
	return (saved);
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
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > 4095)
		return (NULL);
	saved = read_from_fd(fd, saved);
	if (!saved)
		return (NULL);
	line = extract_line(&saved);
	return (line);
}
