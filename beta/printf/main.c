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
#include "ft_printf.h"

int	main(void)
{
	char	*ptr = "abc";
	char	*ptr2 = NULL;
	char	*ptr3 = NULL;
	int		len = 0;
	int		len2 = 0;

	len = ft_printf("str %s\ndigit min %d\ndigit max %d\nmin int %i\nmax int %i\nmin unsigned int %u\nmax unsigned int %u\ntry to print negative number -123456789 as unsigned %u\nmin o %o\nmax o %o\nmin hex %x\nmax hex %x\nUPPER CASE HEX %X\nchar %c\npointer %p\nNULL pointer %p\n%% %%\n",
		"Hello \\n World!", INT_MIN, INT_MAX, INT_MIN, INT_MAX, 0, UINT_MAX, (unsigned int)-123456789, 0, UINT_MAX, 0, UINT_MAX, INT_MAX, 'c', ptr, ptr2);
	ft_printf("=============================================\n");
	len2 = printf("str %s\ndigit min %d\ndigit max %d\nmin int %i\nmax int %i\nmin unsigned int %u\nmax unsigned int %u\ntry to print negative number -123456789 as unsigned %u\nmin o %o\nmax o %o\nmin hex %x\nmax hex %x\nUPPER CASE HEX %X\nchar %c\npointer %p\nNULL pointer %p\n%% %%\n",
		"Hello \\n World!", INT_MIN, INT_MAX, INT_MIN, INT_MAX, 0, UINT_MAX, (unsigned int)-123456789, 0, UINT_MAX, 0, UINT_MAX, INT_MAX, 'c', ptr, ptr2);
	ft_printf("=============================================\n");
	printf("ft_printf len: %d\n", len);
	printf("printf    len: %d\n", len2);
	ft_printf("=============================================\n");
	len = ft_printf(" %s %s %s %s %s \n", " - ", "", "4", "", "2 ");
	ft_printf("=============================================\n");
	len2 = printf(" %s %s %s %s %s \n", " - ", "", "4", "", "2 ");
	ft_printf("=============================================\n");
	printf("ft_printf len: %d\n", len);
	printf("printf    len: %d\n", len2);
	ft_printf("=============================================\n");
	len = ft_printf(" NULL %s NULL \n", ptr3);
	ft_printf("=============================================\n");
	len2 = printf(" NULL %s NULL \n", ptr3);
	ft_printf("=============================================\n");
	printf("ft_printf len: %d\n", len);
	printf("printf    len: %d\n", len2);
	// ft_printf("=============================================\n");
	// len = ft_printf("min o %o\n max o %o\n", 0, UINT_MAX);
	// ft_printf("=============================================\n");
	// len2 = printf("min o %o\n max o %o\n", 0, UINT_MAX);
	// ft_printf("=============================================\n");
	// printf("ft_printf len: %d\n", len);
	// printf("printf    len: %d\n", len2);

	return (0);
}
