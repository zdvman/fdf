/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:24:17 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/15 13:16:41 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (10 + c - 'a');
	if (c >= 'A' && c <= 'F')
		return (10 + c - 'A');
	return (-1);
}

static void	spaces_sign_zerox(const char *str, int *i, int *sign)
{
	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	while (str[*i] != 'x')
		(*i)++;
	(*i)++;
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	i;
	int	sign;
	int	result;
	int	digit;

	i = 0;
	sign = 1;
	result = 0;
	digit = 0;
	spaces_sign_zerox(str, &i, &sign);
	while (str[i])
	{
		digit = get_digit_value(str[i]);
		if (digit == -1 || digit >= str_base)
			break ;
		result = result * str_base + digit;
		i++;
	}
	return (sign * result);
}
