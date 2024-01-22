/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:57:57 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/16 17:57:57 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

void	exit_error(t_stack *stack_a, t_stack *stack_b,
			char **argv, int free_argv_flag)
{
	if (stack_a == NULL || stack_a != NULL)
		free_stack(stack_a);
	if (stack_b == NULL || stack_b != NULL)
		free_stack(stack_b);
	write(2, "Error\n", 6);
	if (free_argv_flag)
		free_argv(argv);
	exit(1);
}

void	exit_program(t_stack *stack_a, t_stack *stack_b,
			char **argv, int free_argv_flag)
{
	if (stack_a == NULL || stack_a != NULL)
		free_stack(stack_a);
	if (stack_b == NULL || stack_b != NULL)
		free_stack(stack_b);
	if (free_argv_flag)
		free_argv(argv);
	exit(1);
}

int	argv_size(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

int	argv_is_nbr(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_isnumber(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
