/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:18:22 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/16 16:12:45 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_index = 0;
	static int	bytes_read = 0;
		
	char	*line = NULL;
	char	*newline_ptr = NULL;
	int		line_len = 0;

	while (1) {
		if (buffer_index >= bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0) {
				if (line_len == 0) {
					return NULL;  // Достигнут конец файла
				} else {
					break;  // Возвращаем последнюю строку
				}
			}
			buffer_index = 0;
		}
		newline_ptr = ft_memchr(buffer + buffer_index, '\n', bytes_read - buffer_index);
		if (newline_ptr)
		{
			int chunk_len = newline_ptr - (buffer + buffer_index) + 1;
			line = ft_realloc(line, line_len + chunk_len);
			if (!line)
				return NULL;  // Ошибка выделения памяти
			ft_memcpy(line + line_len, buffer + buffer_index, chunk_len);
			line_len += chunk_len;
			buffer_index += chunk_len;
			break;
		}
		else
		{
			int chunk_len = bytes_read - buffer_index;
			line = ft_realloc(line, line_len + chunk_len);
			if (!line)
				return NULL;  // Ошибка выделения памяти
			ft_memcpy(line + line_len, buffer + buffer_index, chunk_len);
			line_len += chunk_len;
			buffer_index = bytes_read;
		}
	}

	line[line_len] = '\0';
	return line;
}
