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

#include "../include/ft_printf.h"

int	ft_putnbr(long int n)
{
	int	len;

	len = 0;
	if (n == LONG_MIN) {
		len += ft_putnbr(-(n / 10));
		len += ft_putchar('0' - (n % 10));
		return len;
	}
	if (n < 0)
		n = -n;
	if (n < 10) {
		len += ft_putchar(n + '0');
	} else {
		len += ft_putnbr(n / 10);
		len += ft_putnbr(n % 10);
	}
	return len;
}
