/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:40 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/10 11:12:40 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_print_format(char format_specifier, va_list ap)
{
	int		len;

	len = 0;
	if (format_specifier == 'c')
		len = ft_putchar(va_arg(ap, int));
	else if (format_specifier == 's')
		len = ft_putstr(va_arg(ap, char *));
	else if (format_specifier == 'd')
		len = ft_putnbr((long)va_arg(ap, int), 10);
	else if (format_specifier == 'x')
		len = ft_putnbr((long)va_arg(ap, unsigned int), 16);
	else if (format_specifier == '%')
		len = ft_putchar('%');
	else
		len = ft_putchar(format_specifier);
	return (len);
}
