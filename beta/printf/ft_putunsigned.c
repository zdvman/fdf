/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:51:23 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/23 20:51:23 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned(unsigned long int n, int base, int upper_case, int *len)
{
	char	*hex;

	if (upper_case)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (n < (unsigned int)base)
		return (ft_putchar(hex[n], len));
	else
		return (ft_putunsigned(n / base, base, upper_case, len)
			+ ft_putunsigned(n % base, base, upper_case, len));
}
