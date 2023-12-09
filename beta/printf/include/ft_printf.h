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
# include "../../libft/libft.h"

typedef struct s_print
{
	va_list	args;
	int		wdt;
	int		prc;
	int		zero;
	int		pnt;
	int		dash;
	int		tl;
	int		sign;
	int		is_zero;
	int		perc;
	int		sp;
}	t_print;

void	ft_print_format(char format_specifier, t_print *tab);
int		ft_putnbr(long n, t_print *tab);
int		ft_printf(const char *format, ...);
int		ft_putptr(void *ptr, t_print *tab);
int		ft_putunsigned(unsigned long int n, int base, int upper_case,
			t_print *tab);
int		ft_eval_format(t_print *tab, char *format, int i);

#endif
