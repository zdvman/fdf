/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:01:38 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/20 16:49:57 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libphilo.h"

// void allocate_struct_memory(t_data *data, t_philo *philos, t_fork *forks)
// {
// 	data = (t_data *)malloc(sizeof(t_data));
// 	if (!data)
// 		cleanup(data, RED"Malloc data error!\n"RST, 1);
// 	philos = (t_philo *)malloc(sizeof(t_philo));
// 	if (!philos)
// 		cleanup(data, RED"Malloc philos error!\n"RST, 1);
// 	forks = (t_fork *)malloc(sizeof(t_fork));
// 	if (!forks)
// 		cleanup(data, RED"Malloc forks error!\n"RST, 1);
// }

/*
./philo 5 800 200 200 [5]
*/

int	main(int argc, char **argv)
{
	t_data	data;
	// t_philo	*philos;
	// t_fork	*forks;

	if (argc < 5 || argc > 6)
		ft_error(RED"Argument error!\n"
			G"E.G.: ./philo 5 800 200 200 [5]\n"RST, 1);
	parse_input_args(&data, argc, argv);
	// init_data(data, argv, argc);
	// start_eating();
	// cleanup();
	return (0);
}
