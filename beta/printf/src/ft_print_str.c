/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:12:11 by dzuiev            #+#    #+#             */
/*   Updated: 2023/12/10 18:12:11 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_print_str(char *str, t_print *tab)
{
	int	len;

	if (!str)
	{
		str = "(null)";
		len = 6;
	}
	else
		len = ft_strlen(str);
	if (tab->pnt && tab->prc < len)
		len = tab->prc;
	if (tab->wdt > len)
	{
		if (tab->dash)
		{
			tab->tl += ft_putnstr(str, len);
			tab->tl += ft_putnchar(' ', tab->wdt - len);
		}
		else
		{
			tab->tl += ft_putnchar(' ', tab->wdt - len);
			tab->tl += ft_putnstr(str, len);
		}
	}
	else
		tab->tl += ft_putnstr(str, len);
	return (tab->tl);
}
