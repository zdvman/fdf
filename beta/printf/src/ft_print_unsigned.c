/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:13:09 by dzuiev            #+#    #+#             */
/*   Updated: 2023/12/10 18:13:09 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	ft_unsigned_len(unsigned long int n, int base)
{
	int	len;

	len = 1;
	while (n /= base)
		len++;
	return (len);
}

int	ft_print_unsigned(unsigned long int n, int base, int upper_case, t_print *tab)
{
	int	len;

	len = ft_unsigned_len(n, base);
	if (tab->prc > len)
		tab->prc -= len;
	else
		tab->prc = 0;
	if (tab->wdt > len + tab->prc)
		tab->wdt -= len + tab->prc;
	else
		tab->wdt = 0;
	if (tab->dash)
	{
		tab->tl += ft_putunsigned(n, base, upper_case, tab);
		tab->tl += ft_putnchar('0', tab->prc);
		tab->tl += ft_putnchar(' ', tab->wdt);
	}
	else if (tab->zero && tab->pnt == 0)
	{
		tab->tl += ft_putnchar('0', tab->wdt);
		tab->tl += ft_putunsigned(n, base, upper_case, tab);
	}
	else
	{
		tab->tl += ft_putnchar(' ', tab->wdt);
		tab->tl += ft_putnchar('0', tab->prc);
		tab->tl += ft_putunsigned(n, base, upper_case, tab);
	}
	return (tab->tl);
}
