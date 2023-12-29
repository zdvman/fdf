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
	int	space_count;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (tab->pnt && tab->prc < len)
		len = tab->prc;
	if (tab->wdt > len)
		space_count = tab->wdt - len;
	else
		space_count = 0;
	if (tab->dash) // Выравнивание по левому краю
	{
		tab->tl += ft_putnstr(str, len);
		tab->tl += ft_putnchar(' ', space_count);
	}
	else // Выравнивание по правому краю
	{
		tab->tl += ft_putnchar(' ', space_count);
		tab->tl += ft_putnstr(str, len);
	}
	return (tab->tl);
}
