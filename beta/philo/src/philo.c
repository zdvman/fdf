/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:01:38 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/19 15:04:50 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libphilo.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		ft_error(RED"Argument error!\n"RST, 1);
	printf(RED"Mandatory %s\n"RST, argv[0]);
	printf("Mandatory %s\n", argv[0]);

	return (0);
}
