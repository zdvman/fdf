/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:09:55 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/10 11:09:55 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str, t_print *tab)
{
	if (!str)
	{
		return (ft_putstr("(null)", tab));
	}
	while (*str)
	{
		ft_putchar((int)*str, tab);
		str++;
	}
	return (tab->tl);
}
