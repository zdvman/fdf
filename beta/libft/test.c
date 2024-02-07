/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:45:56 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/07 08:54:49 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <fcntl.h>
// # include <sys/stat.h>
// # include <sys/types.h>
# include "libft.h"

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

static char	*read_from_fd(int fd, char *saved, char *buf)
{
	int		chars_read;
	char	*temp;

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
	static char	*saved = NULL;
	char		*line;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 4095)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	saved = read_from_fd(fd, saved, buf);
	if (!saved)
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	line = extract_line(&saved);
	if (line == NULL)
	{
		free(saved);
		saved = NULL;
	}
	return (line);
}

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

static char	*read_from_fd(int fd, char *saved, char *buf)
{
	int		chars_read;
	char	*temp;

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
	static char	*saved = NULL;
	char		*line;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 4095)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	saved = read_from_fd(fd, saved, buf);
	if (!saved)
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	line = extract_line(&saved);
	if (line == NULL)
	{
		free(saved);
		saved = NULL;
	}
	return (line);
}

static int	file_open(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		write(1, "Error: file open failed\n", 24);
		exit(1);
	}
	return (fd);
}

static int	file_open_old(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY, 0644);
	if (fd < 0)
	{
		write(1, "Error: file open failed\n", 24);
		exit(1);
	}
	return (fd);
}

int main(void)
{
	int fd;
	int i = 0;
	char *line;

	fd = file_open_old("/mnt/c/Users/User/Documents/Зуев Дмитрий/School42/42cursus/beta/libft/text.txt");
	while (i < 2)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		free(line);
		i++;
	}
	close(fd);
}
