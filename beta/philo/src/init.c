/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:13:07 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/19 09:13:07 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libphilo.h"

void	*ft_malloc(t_data *data, size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
		cleanup(data, RED"Malloc error!\n"RST, 1);
	return (ptr);
}

static void philo_init(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].full = false;
		// data->philos[i].last_meal_time = get_time();
		data->philos[i].meals_counter = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_nbr];
	}
}


void init_data(t_data *data)
{
	int	i;

	i = -1;
	data->end_process = false;
	data->philos = ft_malloc(data, sizeof(t_philo) * data->philo_nbr);
	data->forks = ft_malloc(data, sizeof(t_fork) * data->philo_nbr);
	while (++i < data->philo_nbr)
	{
		ft_mutex_handle(&data->forks[i].mtx, INIT, data);
		data->forks[i].id = i;
	}
	i = -1;


}
