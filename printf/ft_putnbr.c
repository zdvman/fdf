/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:11:22 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/10 11:11:22 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int ft_putnbr(long n, int base)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n < 0)
	{
		ft_putchar('-');
		return (ft_putnbr(-n, base) + 1);
	}
	else if (n < base)
	{
		return (ft_putchar(hex[n]));
	}
	else
	{
		return (ft_putnbr(n / base, base) + ft_putnbr(n % base, base));
	}
}
