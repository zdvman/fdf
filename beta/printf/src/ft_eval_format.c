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
	while (!(ft_strchr("iducsopxX%", format[i])) && format[i] != '\0')
	{
		if (format[i] == '-')
			tab->dash = 1;
		else if (format[i] == '0' && format[i - 1] != '.'
			&& format[i - 1] != '0')
			tab->zero = 1;
		else if (format[i] == '0' && format[i - 1] == '.')
			tab->zero = 0;
		else if (format[i] == '#')
			tab->hash = 1;
		else if (format[i] == '.')
			tab->pnt = 1;
		else if (format[i] == ' ')
			tab->sp = 1;
		else if (format[i] == '+')
			tab->sign = 1;
		else if (format[i] >= '0' && format[i] <= '9')
		{
			if (tab->pnt == 0)
				tab->wdt = tab->wdt * 10 + (format[i] - '0');
			else
				tab->prc = tab->prc * 10 + (format[i] - '0');
		}
		i++;
	}
	return (i);
}
