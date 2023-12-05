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

#include "ft_printf.h"

int	ft_putnbr(long n, int *len)
{
	if (n < 0)
	{
		ft_putchar('-', len);
		return (ft_putnbr(-n, len));
	}
	else if (n < 10)
		return (ft_putchar(n + 48, len));
	else
		return (ft_putnbr(n / 10, len) + ft_putnbr(n % 10, len));
}
