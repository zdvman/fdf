/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:41:32 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/16 12:41:32 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *arg)
{
	int	i;

	i = 0;
	if (arg)
	{
		if (ft_issign(arg[i]) && arg[i + 1] != '\0')
			i++;
		while (arg[i] && ft_isdigit(arg[i]))
			i++;
		if (arg[i] != '\0' && !ft_isdigit(arg[i]))
			return (0);
	}
	else
		return (0);
	return (1);
}
