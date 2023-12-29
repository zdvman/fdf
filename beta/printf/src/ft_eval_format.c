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

#include "../include/ft_printf.h"

int	ft_eval_format(t_print *tab, char *format, int i)
{
	int	is_first_digit;

	is_first_digit = 1;
	while (!(ft_strchr("iducsopxX%", format[i])) && format[i] != '\0')
	{
		if (format[i] == '-')
			tab->dash = 1;
		else if (format[i] == '0' && is_first_digit && !tab->pnt)
			tab->zero = 1;
		else if (format[i] == '#')
			tab->hash = 1;
		else if (format[i] == '.')
			tab->pnt = 1;
		else if (format[i] == ' ')
			tab->sp = 1;
		else if (format[i] == '+')
			tab->sign = 1;
		else if (format[i] == '*')
		{
			// Обработка ширины поля, заданной через аргумент
			tab->wdt = va_arg(tab->args, int);
			if (tab->wdt < 0)
			{
				tab->wdt = -tab->wdt;
				tab->dash = 1;
			}
		}
		else if (format[i] >= '0' && format[i] <= '9')
		{
			if (!tab->pnt)
				tab->wdt = tab->wdt * 10 + (format[i] - '0');
			else
				tab->prc = tab->prc * 10 + (format[i] - '0');
		}
		if (ft_isdigit(format[i]))
			is_first_digit = 0;
		i++;
	}
	return (i);
}
