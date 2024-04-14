/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:18:46 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/20 16:49:15 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libphilo.h"

static int	nbr_is_int(const char *str, int i)
{
	int	nbr;

	nbr = 0;
	while (ft_isdigit(str[i]))
	{
		if (nbr > INT_MAX / 10
			|| (nbr == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10))
		{
			return (0);
		}
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

static int	input_is_valid(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (ft_isspace(argv[i][j]))
			j++;
		if (argv[i][j] == '-')
			return (0);
		if (argv[i][j] == '+')
			j++;
		if (!ft_isdigit(argv[i][j]) || !nbr_is_int(argv[i], j))
			return (0);
		i++;
	}
	return (1);
}

void	parse_input_args(t_data *data, int argc, char **argv)
{
	if (!input_is_valid(argc, argv))
		ft_error(RED"Invalid input arguments!\n"
			G"E.G.: ./philo 5 800 200 200 [5]\n"RST, 1);
	data->philo_nbr = ft_atol(argv[1]);
	if (data->philo_nbr > MAX_PHILOS)
		ft_error(RED"Too many philosophers!\n"
			G"Need > 200?: make re MAX_PHILOS=<nbr>\n"RST, 1);
	data->time_to_die = ft_atol(argv[2]) * 1e3;// 1e3 = 1000
	data->time_to_eat = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (data->time_to_die < 6e4
		|| data->time_to_eat < 6e4
		|| data->time_to_sleep < 6e4)
		ft_error(RED"Timestamps must be greater than 60ms!\n", 1);
	if (argc == 6)
		data->meals_limit = ft_atol(argv[5]);
	else
		data->meals_limit = -1;
}
