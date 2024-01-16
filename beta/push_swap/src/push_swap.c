/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:50:51 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/16 13:39:10 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

int	main(int argc, char **argv)
{

	if (argc < 2)
	{
		write(2, "Error\n", 6);	
		return (-1);
	}
	else
		{
			if (!input_validation(argv))
			{
				write(2, "Error\n", 6);
				return (-1);
			}
			else
			{
				if (argc == 2)
				       return (0);
				else
					write(1, "OK\n", 3);
			}
		}
	return (0);
}
