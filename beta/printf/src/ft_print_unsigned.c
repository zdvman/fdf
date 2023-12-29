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

static int	ft_unsigned_len(unsigned long int n, int base, t_print *tab)
{
	int	len;

	len = 1;
	if (tab->hash && n != 0)
	{
		if (base == 8)
			len++;
		else if (base == 16)
			len += 2;
	}
	while (n /= base)
		len++;
	return (len);
}

static void	ft_print_hash(unsigned long int n, int base, int upper_case, t_print *tab)
{
	if (tab->hash && n != 0)
	{
		tab->hash = 0;
		if (base == 8)
			tab->tl += ft_putchar('0');
		else if (base == 16 && !upper_case)
			tab->tl += ft_putstr("0x");
		else if (base == 16 && upper_case)
			tab->tl += ft_putstr("0X");
	}
}

static void	ft_set_len(long long n, t_print *tab, int len)
{
	if (n < 0 || tab->sign || tab->sp)
	{
		if (tab->prc > len - 1)
			tab->prc -= len - 1;
		else
		{
			tab->prc = 0;
			tab->sp = 0;
		}
	}
	else if (tab->prc > len)
		tab->prc -= len;
	else
	{
		tab->prc = 0;
		tab->sp = 0;
	}
	if (tab->wdt > len + tab->prc)
		tab->wdt -= len + tab->prc;
	else
	tab->wdt = 0;
}

int	ft_print_unsigned(unsigned long int n, int base, int upper_case, t_print *tab)
{
	int	len;

	len = ft_unsigned_len(n, base, tab);
	ft_set_len(n, tab, len);
	if (tab->dash)
	{
		ft_print_hash(n, base, upper_case, tab);
		tab->tl += ft_putnchar('0', tab->prc);
		ft_putunsigned(n, base, upper_case, tab);
		tab->tl += ft_putnchar(' ', tab->wdt);
	}
	else if (tab->zero && tab->pnt == 0)
	{
		ft_print_hash(n, base, upper_case, tab);
		tab->tl += ft_putnchar('0', tab->wdt);
		ft_putunsigned(n, base, upper_case, tab);
	}
	else
	{
		tab->tl += ft_putnchar(' ', tab->wdt);
		ft_print_hash(n, base, upper_case, tab);
		tab->tl += ft_putnchar('0', tab->prc);
		ft_putunsigned(n, base, upper_case, tab);
	}
	return (tab->tl);
}
