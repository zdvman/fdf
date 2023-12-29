/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:40 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/10 17:33:49 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	ft_print_format(char format_specifier, t_print *tab)
{
	if (format_specifier == 'c')
		ft_print_char(va_arg(tab->args, int), tab);
	else if (format_specifier == 's')
		ft_print_str(va_arg(tab->args, char *), tab);
	else if (format_specifier == 'i' || format_specifier == 'd')
		ft_print_nbr((long)va_arg(tab->args, int), tab);
	else if (format_specifier == 'u')
		ft_print_unsigned(va_arg(tab->args, unsigned int), 10, 0, tab);
	else if (format_specifier == 'o')
		ft_print_unsigned(va_arg(tab->args, unsigned int), 8, 0, tab);
	else if (format_specifier == 'x')
		ft_print_unsigned(va_arg(tab->args, unsigned int), 16, 0, tab);
	else if (format_specifier == 'X')
		ft_print_unsigned(va_arg(tab->args, unsigned int), 16, 1, tab);
	else if (format_specifier == 'p')
		ft_print_ptr(va_arg(tab->args, void *), tab);
	else if (format_specifier == '%')
		tab->tl += ft_putchar('%');
}
