/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:56:07 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/10 13:28:48 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct	s_flags
{
	int			plus;
	int			minus;
	int			space;
	int			hash;
	int			zero;
	int			width;
	int			precision;
	int			length;
	int			upper_case;
}				t_flags;

int	ft_putchar(int c, int *len);
int	ft_putstr(char *str, int *len);
int	ft_putnbr(long n, int *len);
int	ft_printf(const char *format, ...);
int	ft_putptr(void *ptr, int *len);
int	ft_putunsigned(unsigned long int n, int base, int upper_case, int *len);
int	*ft_print_format(char format_specifier, va_list ap, int *len);

#endif
