/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:08:19 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/19 09:55:18 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libphilo.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		ft_error("Argument error!\n", 1);
	printf("Bonus %s\n", argv[0]);
	return (0);
}
