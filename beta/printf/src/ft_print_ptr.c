/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:28:41 by dzuiev            #+#    #+#             */
/*   Updated: 2023/12/10 20:28:41 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	ft_unsigned_len(unsigned long long int n, int base)
{
	int	len;

	len = 1;
	while (n /= base)
		len++;
	return (len);
}

int	ft_print_ptr(void *ptr, t_print *tab)
{
	int	len;

	if (ptr == NULL)
		len = 5;
	else
		len = ft_unsigned_len((unsigned long long int)ptr, 16) + 2;
	len = tab->wdt - len;
	if (tab->dash)
	{
		tab->tl += ft_putptr(ptr, tab);
		if (len > 0)
			tab->tl += ft_putnchar(' ', len);
	}
	else
	{
		if (len > 0)
			tab->tl += ft_putnchar(' ', len);
		tab->tl += ft_putptr(ptr, tab);
	}
	return (tab->tl);
}
