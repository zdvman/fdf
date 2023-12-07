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

int	ft_putnbr(long n, t_print *tab)
{
	if (n < 0)
	{
		ft_putchar('-', tab);
		return (ft_putnbr(-n, tab));
	}
	else if (n < 10)
		return (ft_putchar(n + 48, tab));
	else
		return (ft_putnbr(n / 10, tab) + ft_putnbr(n % 10, tab));
}
