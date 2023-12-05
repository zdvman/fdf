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

#include "ft_printf.h"

int	*ft_print_format(char format_specifier, va_list ap, int *len)
{
	if (format_specifier == 'c')
		ft_putchar(va_arg(ap, int), len);
	else if (format_specifier == 's')
		ft_putstr(va_arg(ap, char *), len);
	else if (format_specifier == 'd')
		ft_putnbr((long)va_arg(ap, int), len);
	else if (format_specifier == 'i')
		ft_putnbr((long)va_arg(ap, int), len);
	else if (format_specifier == 'u')
		ft_putunsigned(va_arg(ap, unsigned int), 10, 0, len);
	else if (format_specifier == 'o')
		ft_putunsigned(va_arg(ap, unsigned int), 8, 0, len);
	else if (format_specifier == 'x')
		ft_putunsigned(va_arg(ap, unsigned int), 16, 0, len);
	else if (format_specifier == 'X')
		ft_putunsigned(va_arg(ap, unsigned int), 16, 1, len);
	else if (format_specifier == 'p')
		ft_putptr(va_arg(ap, void *), len);
	else if (format_specifier == '%')
		ft_putchar('%', len);
	return (len);
}
