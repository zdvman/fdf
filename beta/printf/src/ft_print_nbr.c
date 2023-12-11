/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:27:02 by dzuiev            #+#    #+#             */
/*   Updated: 2023/12/10 18:27:02 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	ft_nbr_len(long int n, t_print *tab)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	else if (tab->sign || tab->sp)
		len++;
	while (n /= 10)
		len++;
	return (len);
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

static int	ft_print_sign(long int n, t_print *tab)
{
	int	len;

	len = 0;
	if (tab->sign && n > 0)
		len += ft_putchar('+');
	else if (tab->sp && n > 0)
		len += ft_putchar(' ');
	tab->sign = 0;
	tab->sp = 0;
	return (len);
}

int	ft_print_nbr(long int n, t_print *tab)
{
	int	len;

	len = ft_nbr_len(n, tab);
	ft_set_len(n, tab, len);
	if (tab->dash)
	{
		tab->tl += ft_print_sign(n, tab);
		tab->tl += ft_putnchar('0', tab->prc);
		tab->tl += ft_putnbr(n);
		tab->tl += ft_putnchar(' ', tab->wdt);
	}
	else if (tab->zero && tab->pnt == 0)
	{
		tab->tl += ft_print_sign(n, tab);
		tab->tl += ft_putnchar('0', tab->wdt);
		tab->tl += ft_putnbr(n);
	}
	else
	{
		tab->tl += ft_putnchar(' ', tab->wdt);
		tab->tl += ft_print_sign(n, tab);
		tab->tl += ft_putnchar('0', tab->prc);
		tab->tl += ft_putnbr(n);
	}
	return (tab->tl);
}
