/* ************************************************************************** */
/*                                                                      */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:43:38 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/10 13:28:10 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static t_print	*ft_initialise_tab(t_print *tab)
{
	tab->wdt = 0;
	tab->prc = 0;
	tab->zero = 0;
	tab->pnt = 0;
	tab->sign = 0;
	tab->dash = 0;
	tab->hash = 0;
	tab->sp = 0;
	return (tab);
}

int	ft_printf(const char *format, ...)
{
	t_print	*tab;
	int		len;
	int		i;

	i = -1;
	tab = (t_print *)malloc(sizeof(t_print));
	if (!tab)
		return (-1);
	tab = ft_initialise_tab(tab);
	tab->tl = 0;
	va_start(tab->args, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i = ft_eval_format(tab, (char *)format, ++i);
			ft_print_format(format[i], tab);
			ft_initialise_tab(tab);
		}
		else
			tab->tl += ft_putchar(format[i]);
	}
	va_end(tab->args);
	len = tab->tl;
	free(tab);
	return (len);
}
