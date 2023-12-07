/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:13:02 by dzuiev            #+#    #+#             */
/*   Updated: 2023/12/07 17:13:02 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_eval_format(t_print *tab, char *format, int i)
{
	while (format[i] != 'u' && format[i] != 'd' && format[i] != 'c'
		&& format[i] != 's' && format[i] != 'u' && format[i] != 'p'
		&& format[i] != 'x' && format[i] != 'X' && format[i] != '%'
		&& format[i] != 'i' && format[i] != 'o' && format[i] != '\0')
	{
		if (*format == '-')
			tab->dash = 1;
		else if (*format == '0')
			tab->zero = 1;
		else if (*format == '.')
			tab->pnt = 1;
		else if (*format == ' ')
			tab->sp = 1;
		else if (*format == '+')
			tab->sign = 1;
		else if (*format >= '0' && *format <= '9')
		{
			if (tab->pnt == 0)
				tab->wdt = tab->wdt * 10 + (*format - '0');
			else
				tab->prc = tab->prc * 10 + (*format - '0');
		}
		i++;
	}
	return (i);
}
