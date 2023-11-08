/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:45:00 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/04 20:28:30 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_whitespaces(const char *nptr)
{
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	return (nptr);
}

static int	ft_sign(const char *nptr)
{
	int	sign;
	int	num_of_signs;

	num_of_signs = 0;
	sign = 1;
	while (*nptr == '-' || *nptr == '+')
	{
		num_of_signs++;
		if (*nptr == '-' && num_of_signs == 1)
			sign = -1;
		nptr++;
	}
	if (num_of_signs == 0)
		return (0);
	else if (num_of_signs == 1)
		return (sign);
	else
		return (num_of_signs);
}

static long int	ft_handledigits(const char *nptr)
{
	long int	num;

	num = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = num * 10 + (*nptr - 48);
		nptr++;
	}
	return (num);
}

int	ft_atoi(const char *nptr)
{
	const char	*ptr;
	long int	num;
	int			sign;

	num = 0;
	ptr = ft_whitespaces(nptr);
	sign = ft_sign(ptr);
	if (sign > 1)
		return (0);
	else if (sign == 1 || sign == -1)
		ptr++;
	else
		sign = 1;
	num = ft_handledigits(ptr);
	return (num *= sign);
}
/*
int	main(int argc, char **argv)
{
	int	a = 0;
	int b = 0;

	if (argc == 2)
	{
		printf("%i\n", argc);
		printf("%s\n", argv[1]);
		a = atoi(argv[1]);
		b = ft_atoi(argv[1]);
		printf("a : %i\n", a);
		printf("b : %i\n", b);
	}
	return (0);
}
*/
