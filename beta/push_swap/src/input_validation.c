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

int	input_validation(char **argv, int i)
{
	while (argv[i])
	{
		if (!ft_isnumber(argv[i]) || ft_strisempty(argv[i])
			|| ft_strisspace_only(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
