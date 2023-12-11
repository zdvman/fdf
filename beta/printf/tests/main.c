/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:25:01 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/10 17:54:01 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include "../include/ft_printf.h"

int	main(void)
{
	char	*ptr = "abc";
	char	*ptr2 = NULL;
	char	*ptr3 = NULL;
	int		len = 0;
	int		len2 = 0;
	void 	*ptr1 = &ptr1;

	len += printf("str %s\ndigit min %d\ndigit max %d\nmin int %i\nmax int %i\nmin unsigned int %u\nmax unsigned int %u\ntry to print negative number -123456789 as unsigned %u\nmin o %o\nmax o %o\nmin hex %x\nmax hex %x\nUPPER CASE HEX %X\nchar %c\npointer %p\nNULL pointer %p\n%% %%\n",
		"Hello \\n World!", INT_MIN, INT_MAX, INT_MIN, INT_MAX, 0, UINT_MAX, (unsigned int)-123456789, 0, UINT_MAX, 0, UINT_MAX, INT_MAX, 'c', ptr, ptr2);
	len2 += ft_printf("str %s\ndigit min %d\ndigit max %d\nmin int %i\nmax int %i\nmin unsigned int %u\nmax unsigned int %u\ntry to print negative number -123456789 as unsigned %u\nmin o %o\nmax o %o\nmin hex %x\nmax hex %x\nUPPER CASE HEX %X\nchar %c\npointer %p\nNULL pointer %p\n%% %%\n",
		"Hello \\n World!", INT_MIN, INT_MAX, INT_MIN, INT_MAX, 0, UINT_MAX, (unsigned int)-123456789, 0, UINT_MAX, 0, UINT_MAX, INT_MAX, 'c', ptr, ptr2);
	// ft_printf("=============================================\n");
	ft_printf("=============================================\n");
	printf("printf    len: %d\n", len);
	printf("ft_printf len: %d\n", len2);
	ft_printf("=============================================\n");
	// len = ft_printf(" %s %s %s %s %s \n", " - ", "", "4", "", "2 ");
	// ft_printf("=============================================\n");
	// len2 = printf(" %s %s %s %s %s \n", " - ", "", "4", "", "2 ");
	// ft_printf("=============================================\n");
	// printf("ft_printf len: %d\n", len);
	// printf("printf    len: %d\n", len2);
	ft_printf("=============================================\n");
	len += printf(" NULL %10.2s NULL \n", ptr3);
	// ft_printf("=============================================\n");
	len2 += ft_printf(" NULL %10.2s NULL \n", ptr3);
	ft_printf("=============================================\n");
	// printf("ft_printf len: %d\n", len);
	// printf("printf    len: %d\n", len2);
	// ft_printf("=============================================\n");
	// len = ft_printf("min o %o\n max o %o\n", 0, UINT_MAX);
	// ft_printf("=============================================\n");
	// len2 = printf("min o %o\n max o %o\n", 0, UINT_MAX);
	// ft_printf("=============================================\n");
	// printf("ft_printf len: %d\n", len);
	// printf("printf    len: %d\n", len2);
	// printf("%%5-d    123 - \"%-5d\"\n", 123);
	// printf("%%3.3 123456 - \"%3.3s\"\n", "123456");
	// printf("%%.3s 123456 - \"%.3s\"\n", "123456");
	// printf("%%.0s 123456 - \"%.0s\"\n", "123456");
	// printf("%%.d  123456 - \"%.d\"\n", 123456);
	// // printf("%%#d  123456 - \"%#d\"\n", 123456);
	// printf("%%30s 123456 - \"%30s\"\n", "123456");	
	// printf("%%3s 123456 - \"%3s\"\n", "123456");	
	// printf("%%.2d    123 - \"%.2d\"\n", 123);
	// printf("%%+.2d   123 - \"%+.2d\"\n", 123);
	// printf("%%+.5d  -123 - \"%+.5d\"\n", -123);
	// printf("%%+.d   -123 - \"%+.d\"\n", -123);
	// printf("%%02d    123 - \"%02d\"\n", 123);
	// printf("%%+05d  +123 - \"%+05d\"\n", 123);
	// printf("%%+5d   +123 - \"%+5d\"\n", 123);
	// printf("%%+5d   -123 - \"%+5d\"\n", -123);
	// printf("%%+05d  -123 - \"%+05d\"\n", -123);
	// printf("%%0+5d  -123 - \"%0+5d\"\n", -123);
	// printf("%%10d    123 - \"%10d\"\n", 123);
	// printf("%%0#o    123 - \"%0#o\"\n", 123);
	// printf("%%#50x     0 - \"%#50x\"\n", 0);
	// printf("%%#05X   123 - \"%#05X\"\n", 123);
	// printf("%% d       1 - \"% d\"\n", 1);
	// printf("%% 02d     1 - \"% 02d\"\n", 1);
	// printf("%%0 3d     1 - \"%0 3d\"\n", 1);
	// printf("%s\n", ft_strchr("iduc%sopxX", '%'));
	// len = ft_printf("%%#o %#o\n%%#x %#x\n%%#X %#X\n%%#o %#o\n%%#x %#x\n%%#X %#X\n", 123, 123, 123, 0, 0, 0);
	// ft_printf("=============================================\n");
	// len2 = printf("%%#o %#o\n%%#x %#x\n%%#X %#X\n%%#o %#o\n%%#x %#x\n%%#X %#X\n", 123, 123, 123, 0, 0, 0);
	// ft_printf("=============================================\n");
	// %c Tests
	len += printf("%%c: %c\n", 'a');              // Без флагов
	len2 += ft_printf("%%c: %c\n", 'a');
	len += printf("%%-5c: %-5c\n", 'b');          // Флаг '-'
	len2 += ft_printf("%%-5c: %-5c\n", 'b');

	// %s Tests
	len += printf("%%s: %s\n", "test");           // Без флагов
	len2 += ft_printf("%%s: %s\n", "test");
	len += printf("%%20s: %20s\n", "right");       // Ширина поля
	len2 += ft_printf("%%20s: %20s\n", "right");
	len += printf("%%-20s: %-20s\n", "left");      // Флаг '-' с шириной поля
	len2 += ft_printf("%%-20s: %-20s\n", "left");
	len += printf("%%.5s: %.5s\n", "truncate");    // Точность
	len2 += ft_printf("%%.5s: %.5s\n", "truncate");

	// %p Tests
	len += printf("%%p: %p\n", ptr1);               // Без флагов
	len2 += ft_printf("%%p: %p\n", ptr1);

	// %d и %i Tests
	len += printf("%%d: %d\n", 12345);             // Без флагов
	len2 += ft_printf("%%d: %d\n", 12345);
	len += printf("%%+10d: %+10d\n", 12345);       // Флаг '+' с шириной поля
	len2 += ft_printf("%%+10d: %+10d\n", 12345);
	len += printf("%% 10d: % 10d\n", 12345);       // Флаг ' ' (пробел) с шириной поля
	len2 += ft_printf("%% 10d: % 10d\n", 12345);

	// %u Tests
	len += printf("%%u: %u\n", 12345u);            // Без флагов
	len2 += ft_printf("%%u: %u\n", 12345u);

	// %x и %X Tests
	len += printf("%%x: %x\n", 0x123abc);          // Без флагов
	len2 += ft_printf("%%x: %x\n", 0x123abc);
	len += printf("%%X: %X\n", 0x123abc);          // Без флагов
	len2 += ft_printf("%%X: %X\n", 0x123abc);
	len += printf("%%#x: %#x\n", 0x123abc);        // Флаг '#'
	len2 += ft_printf("%%#x: %#x\n", 0x123abc);
	len += printf("%%#X: %#X\n", 0x123abc);        // Флаг '#' для %X
	len2 += ft_printf("%%#X: %#X\n", 0x123abc);

	// %% Tests
	len += printf("%%%%\n");                       // Вывод символа '%'
	len2 += ft_printf("%%%%\n");

	printf("=============================================\n");
	printf("printf    len: %d\n", len);
	printf("ft_printf len: %d\n", len2);

	return (0);
}
