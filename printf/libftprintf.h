/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:56:07 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/10 12:56:07 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

int	ft_putchar(int c);
int	ft_putstr(char *str);
int ft_putnbr(long n, int base);
int	ft_print_format(char format_specifier, va_list ap);
int	ft_printf(const char *format, ...);

#endif
