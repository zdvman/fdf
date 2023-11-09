/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:43:38 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/09 18:43:38 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

int		ft_putchar(int c)
{
	return write(1, &c, 1);
}

int		ft_putstr(char *str)
{
	int		len;

	len = 0;
	while (*str)
	{
		ft_putchar((int)*str);
		str++;
		len++;
	}
	return (len);
}

int ft_putnbr(long n, int base)
{
	// int		len;
	char	*hex;

	// len = 0;
	hex = "0123456789abcdef";
	if (n < 0)
	{
		ft_putchar('-');
		return (ft_putnbr(-n, base) + 1);
	}
	else if (n < base)
	{
		return (ft_putchar(hex[n]));
	}
	else
	{
		return (ft_putnbr(n / base, base) + ft_putnbr(n % base, base));
	}
}

int	ft_print_format(char format_specifier, va_list ap)
{
	int		len;

	len = 0;
	if (format_specifier == 'c')
	{
		len = ft_putchar(va_arg(ap, int));
	}
	else if (format_specifier == 's')
	{
		len = ft_putstr(va_arg(ap, char *));
	}
	else if (format_specifier == 'd')
	{
		len = ft_putnbr((long)va_arg(ap, int), 10);
	}
	else if (format_specifier == 'x')
	{
		len = ft_putnbr((long)va_arg(ap, unsigned int), 16);
	}
	else if (format_specifier == '%')
	{
		len = ft_putchar('%');
	}
	else
	{
		len = ft_putchar(format_specifier);
	}
	return (len);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			len;

	len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			len += ft_print_format(*(++format), ap);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (len);
}

int		main(void)
{
	// int		count;

	ft_printf("Hello %s, today is %d, in hex %x, char %c, and %%\n", "world", 20161109, 20161109, 'a');
	printf("Hello %s, today is %d, in hex %x, char %c, and %%\n", "world", 20161109, 20161109, 'a');


/*
	count = ft_printf("%d\n", INT_MIN);
	ft_printf("The chars written are %d\n", count);
	count = printf("%d\n", INT_MIN);
	printf("The chars written are %d\n", count);
	return (0);
*/
}
