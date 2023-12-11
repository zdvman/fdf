/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:11:50 by dzuiev            #+#    #+#             */
/*   Updated: 2023/12/10 18:11:50 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_print_char(int c, t_print *tab)
{
	if (tab->wdt > 1)
	{
		if (tab->dash)
		{
			tab->tl += ft_putchar(c);
			tab->tl += ft_putnchar(' ', tab->wdt - 1);
		}
		else
		{
			tab->tl += ft_putnchar(' ', tab->wdt - 1);
			tab->tl += ft_putchar(c);
		}
	}
	else
		tab->tl += ft_putchar(c);
	return (tab->tl);
}
