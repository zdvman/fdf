/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:26:10 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/21 20:38:10 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		saved = NULL;
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
	static char	*saved[4096] = {0};
	char		*line;
//	char		*temp;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 4095)
		return (NULL);
//	if (!saved[fd])
//		saved[fd] = ft_strdup("");
	saved[fd] = read_from_fd(fd, saved[fd]);
	if (!saved[fd])
	{
		free(saved[fd]);
		saved[fd] = NULL;
		return (NULL);
	}
//	saved[fd] = temp;
	line = extract_line(&saved[fd]);
	if (line == NULL)
	{
		free(saved[fd]);
		saved[fd] = NULL;
	}
	return (line);
}
