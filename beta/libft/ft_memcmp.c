/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:01:41 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/06 11:15:59 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
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
		printf("s1 : %s; s2 : %s; n : %zu\n", argv[1], argv[2], n);
		a = strcpy(a, argv[1]);
		b = strcpy(b, argv[2]);
		printf("Результат срвнения в memcmp   : %i\n", memcmp(argv[1], argv[2], n));
		printf("Результат срвнения в ft_memcmp: %i\n", ft_memcmp(a, b, n));
	}
	free(a);
	free(b);
	return (0);
}
*/
