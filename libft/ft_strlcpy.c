/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:09:53 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/01 19:53:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
