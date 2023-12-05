/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:06:28 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/23 20:06:28 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr, int *len)
{
	if (ptr == NULL)
		return (ft_putstr("(nil)", len));
	else
		ft_putstr("0x", len);
	return (ft_putunsigned((unsigned long long int)ptr, 16, 0, len));
}
