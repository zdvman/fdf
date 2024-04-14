/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:48:48 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/25 21:11:06 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int	ft_strlen(char *str)
{
	if (!str)
		return (0);
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(char *str, char c)
{
	int i = 0;
	
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup(char *str)
{
	char	*new = NULL;
	int		len = ft_strlen(str);

	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	int i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new = NULL;
	int		len1;
	int		len2;

	if (!s2)
		return NULL;
	len2 = ft_strlen(s2);
	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	new = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (new == NULL)
		return (NULL);
	int i = 0;
	if (s1)
	{
		while (*s1)
		{
			new[i] = *s1;
			s1++;
			i++;
		}
	}
	if (s2)
	{
		while (*s2)
		{
			new[i] = *s2;
			s2++;
			i++;
		}
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	if (!src || !dest)
		return (NULL);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_line(char **saved)
{
	int i = 0;
	char *tmp_saved = *saved;
	char *line = NULL;
	char *tmp = NULL;
	int len = 0;

	if (tmp_saved)
	{
		while (tmp_saved[i])
		{
			if (tmp_saved[i] == '\n')
			{
				line = (char *)malloc(sizeof(char) * (i + 2));
				if (line == NULL)
					return (NULL);
				line = ft_strncpy(line, tmp_saved, i + 1);
				tmp = tmp_saved;
				tmp_saved = ft_strdup(&tmp_saved[i + 1]);
				free(tmp);
				tmp = NULL;
				return (line);
			}
			i++;
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char *saved = NULL;
	char	*line = NULL;
	char	*buf = NULL;
	char	*tmp = NULL;
	int chars_read = 0;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 4095)
		return (NULL);
	if (saved)
	{
		if (line = get_line(&saved))
			return (line);
	}
	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (buf == NULL)
		return (NULL);
	while ((chars_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[chars_read] = '\0';
		tmp = saved;
		saved = ft_strjoin(saved, buf);
		free(tmp);
		tmp =  NULL;
		if (line = get_line(&saved))
			return (line);
	}
	free(buf);
	buf = NULL;
	if (chars_read < 0)
	{
		if (buf)
			free(buf);
		if (line)
			free(line);
		if (saved)
			free(saved);
	}
	else if (chars_read == 0)
	{
		if (saved)
				return (saved);
		else
			return (NULL);
	}
	return (NULL);
}

int	main(void)
{
	int fd;
	char *line = NULL;

	fd = open("file", O_RDONLY, 0777);
	while(line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}
