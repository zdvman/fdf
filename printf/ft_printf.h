/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:56:07 by dzuiev            #+#    #+#             */
/*   Updated: 2023/12/05 17:30:14 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int	ft_putchar(int c, int *len);
int	ft_putstr(char *str, int *len);
int	ft_putnbr(long n, int *len);
int	ft_printf(const char *format, ...);
int	ft_putptr(void *ptr, int *len);
int	ft_putunsigned(unsigned long int n, int base, int upper_case, int *len);
int	*ft_print_format(char format_specifier, va_list ap, int *len);

#endif
