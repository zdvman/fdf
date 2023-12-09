/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:28:35 by dzuiev            #+#    #+#             */
/*   Updated: 2023/12/09 15:28:35 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	int	len;

	len = 0;
	if (s == NULL)
	{
		len += write(1, "(null)", 6);
		return (len);
	}
	while (*s)
		len += write(1, s++, sizeof(char));
	return (len);
}
