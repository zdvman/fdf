/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:30:57 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/22 12:33:32 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

int	ft_putchar(int c, int *len)
{
	*len += write(1, &c, 1);\
	return (*len);
}

int ft_putstr(char *str, int *len)
{
	while (*str)
	{
		*len += write(1, str, 1);
		str++;
	}
	return (*len);
}

int ft_putnbr(long nbr, int *len)
{
	if (nbr < 0)
	{
		ft_putchar(45, len);
		return (ft_putnbr(-nbr, len));
	}
	else if (nbr < 10)
		return (ft_putchar(nbr + 48, len));
	else
		return (ft_putnbr(nbr / 10, len) + ft_putnbr(nbr % 10, len));
}

int	print_format(int specifier, va_list ap, int *len)
{
	if (specifier == 'd' || specifier == 'i')
		ft_putnbr((long)va_arg(ap, int), len);
	else if (specifier == 'c')
		ft_putchar(va_arg(ap, int), len);
	else if (specifier == 's')
		ft_putstr(va_arg(ap, char *), len);
	else if (specifier == '%')
		ft_putchar('%', len);
}

int	ft_printf(const char* format, ...)
{
	va_list ap;
	int	len;

	len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
			print_format(*(++format), ap, &len);
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (len);
}

int main(void)
{
	int len = 0;
	int len1 = 0;

	len = printf("i: %i, d: %d, c: %c, s: %s\n", INT_MIN, INT_MAX, 'a', "hello");
	len1 = ft_printf("i: %i, d: %d, c: %c, s: %s\n", INT_MIN, INT_MAX, 'a', "hello");
	printf("printf len:    %d\nft_printf len: %d\n", len, len1);
	return (0);
}
