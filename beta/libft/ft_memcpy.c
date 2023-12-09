/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:02:09 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/07 20:49:14 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
*/
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*ptr_src;
	unsigned char		*ptr_dest;

	if (!dest && !src)
		return (NULL);
	ptr_dest = (unsigned char *)dest;
	ptr_src = (const unsigned char *)src;
	while (n--)
		*ptr_dest++ = *ptr_src++;
	return (dest);
}

/*
int	main(int argc, char **argv)
{
	char	*a;
	char	*b;
	size_t	n;

	if (argc == 4)
	{
		n = (size_t)(atoi(argv[3])); 
		a = (char *)malloc(sizeof(char) * strlen(argv[1]));
		if (!a)
			return (-1);
		b = (char *)malloc(sizeof(char) * strlen(argv[2]));
		if (!b)
			return (-1);
		printf("argc : %i\n", argc);
		printf("dest : %s; src : %s; n : %zu\n", argv[1], argv[2], n);
		a = strcpy(a, argv[1]);
		b = strcpy(b, argv[1]);
		printf("Результат копирования в memcpy   : %s\n",
			(char *)memcpy(a, argv[2], n));
		printf("Результат копирования в ft_memcpy: %s\n",
			(char *)ft_memcpy(b, argv[2], n));
	}
	free(a);
	free(b);
	return (0);
}
*/
