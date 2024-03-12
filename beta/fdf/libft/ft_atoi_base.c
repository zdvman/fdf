/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:24:17 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/12 17:31:05 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int get_digit_value(char c)
{
	if (c >= '0' && c <= '9') 
		return c - '0';
	if (c >= 'a' && c <= 'f') 
		return 10 + c - 'a';
	if (c >= 'A' && c <= 'F') 
		return 10 + c - 'A';
	return -1;
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	i = 0;
	int	sign = 1;
	int	result = 0;
	int	digit = 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != 'x')
		i++;
	i++;
	while (str[i])
	{
		digit = get_digit_value(str[i]);
		if (digit == -1 || digit >= str_base)
			break;
		result = result * str_base + digit;
		i++;
	}
	return sign * result;
}
