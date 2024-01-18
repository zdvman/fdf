/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:54:18 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/18 13:20:46 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	int		i;
	// int		flag;

	stack_a = NULL;
	i = 0;
	// flag = 0;
	if (argc < 2 || (ft_strisempty(argv[1]) && argc == 2))
		return (1);
	else if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		// flag = 1;
	}
	if (!input_validation(argv, !(argc == 2)))
		error_exit(NULL, NULL);
	else
	{
		stack_a = fill_stack_with_values(argv_size(argv), argv, !(argc == 2));
		if (!stack_sorted(stack_a))
			write(1, "NOT SORTED\n", 11);
		else
			write(1, "SORTED\n", 7);
	}
	free_stack(stack_a);
	return (0);
}
