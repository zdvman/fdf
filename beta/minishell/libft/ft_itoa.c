/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:54:25 by dzuiev            #+#    #+#             */
/*   Updated: 2023/10/30 10:54:30 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	unsigned int	tmp;
	int				i;

	i = 1;
	if (n < 0)
	{
		tmp = (unsigned int)(-n);
		i++;
	}
	else
		tmp = (unsigned int)n;
	while (tmp >= 10)
	{
		tmp /= 10;
		i++;
	}
	return (i);
}

static unsigned int	ft_tenpow(int n)
{
	unsigned int	result;
	int				i;

	result = 1;
	i = -1;
	while (++i < n)
	{
		result *= 10;
	}
	return (result);
}

static unsigned int	get_divisor(int n)
{
	unsigned int	divisor;

	if (n < 0)
		divisor = ft_tenpow(ft_intlen(n) - 2);
	else
		divisor = ft_tenpow(ft_intlen(n) - 1);
	return (divisor);
}

char	*ft_itoa(int n)
{
	unsigned int	divisor;
	char			*num;
	char			*tmp;

	divisor = get_divisor(n);
	tmp = (char *)malloc(ft_intlen(n) + 1);
	if (!tmp)
		return (NULL);
	num = tmp;
	if (n < 0)
	{
		*num++ = '-';
		n *= -1;
	}
	while (divisor > 0)
	{
		*num++ = n / divisor + 48;
		n %= divisor;
		divisor /= 10;
	}
	*num = '\0';
	return (tmp);
}

/*
static unsigned int	ft_tenpow(int n)
{
	if (n == 0)
		return (1);
	else
		return (10 * ft_tenpow(n - 1));
}
*/
