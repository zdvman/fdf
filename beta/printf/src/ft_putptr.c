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

#include "../../libft/libft.h"
#include "../include/ft_printf.h"

int	ft_putptr(void *ptr, t_print *tab)
{
	if (ptr == NULL)
	{
		tab->tl += ft_putstr("(nil)");
		return (tab->tl);
	}
	else
		tab->tl += ft_putstr("0x");
	return (ft_putunsigned((unsigned long long int)ptr, 16, 0, tab));
}
