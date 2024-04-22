/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:18:40 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/22 12:54:29 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	buffer_init(t_dynamic_buffer *buf)
{
	buf->data = malloc(64);
	buf->len = 0;
	if (buf->data)
	{
		buf->capacity = 64;
		buf->data[0] = '\0';
	}
	else
	{
		buf->capacity = 0;
	}
}

void	buffer_free(t_dynamic_buffer *buf)
{
	free(buf->data);
	buf->data = NULL;
	buf->len = 0;
	buf->capacity = 0;
}

int	buffer_append(t_dynamic_buffer *buf, const char *str, size_t n)
{
	char	*new_data;
	size_t	new_capacity;

	if (buf->len + n + 1 > buf->capacity)
	{
		new_data = NULL;
		new_capacity = buf->capacity * 2;
		while (new_capacity < buf->len + n + 1)
			new_capacity *= 2;
		new_data = ft_realloc(buf->data, new_capacity);
		if (!new_data)
			return (0);
		buf->data = new_data;
		buf->capacity = new_capacity;
	}
	ft_memcpy(buf->data + buf->len, str, n);
	buf->len += n;
	buf->data[buf->len] = '\0';
	return (1);
}

void	buffer_clear(t_dynamic_buffer *buf)
{
	buf->len = 0;
	if (buf->data)
		buf->data[0] = '\0';
}
