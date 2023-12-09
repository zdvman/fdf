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

int	ft_putnbr(long n, t_print *tab)
{
	if (n < 0)
	{
		tab->tl += ft_putchar('-');
		return (ft_putnbr(-n, tab));
	}
	else if (n < 10)
	{
		tab->tl += ft_putchar(n + 48);
		return (tab->tl);
	}
	else
		return (ft_putnbr(n / 10, tab) + ft_putnbr(n % 10, tab));
}
