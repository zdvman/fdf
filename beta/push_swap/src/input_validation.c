/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:49:38 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/16 12:49:38 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

int	input_validation(char **argv)
{
	int	i;
	int	count_zeros;

	i = 1;
	count_zeros = 0;
	while (argv[i])
	{
		if (!ft_isnumber(argv[i]) || ft_isempty(argv[i]))
			return (0);
		count_zeros += ft_iszero(argv[i]);
		i++;
	}
	if (count_zeros > 1)
		return (0);
	if (ft_duplicates_found(argv))
		return (0);
	return (1);
}
