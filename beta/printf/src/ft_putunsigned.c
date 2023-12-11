/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:51:23 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/23 20:51:23 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

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

int	ft_putunsigned(unsigned long int n, int base, int upper_case, t_print *tab)
{
	char	*hex;

	if (upper_case)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	ft_print_hash(n, base, upper_case, tab);
	if (n < (unsigned long int)base)
	{
		tab->tl += ft_putchar(hex[n]);
		return (tab->tl);
	}
	else
		return (ft_putunsigned(n / base, base, upper_case, tab)
			+ ft_putunsigned(n % base, base, upper_case, tab));
}
