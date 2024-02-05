/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:54:18 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/05 18:53:15 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

static void	print_stack(t_stack **stack)
{
	while (*stack)
	{
		printf("%d\n", (*stack)->value);
		(*stack) = (*stack)->next;
	}
}

int	main(int argc, char **argv)
{
	t_stack	**stack_a;
	t_stack	**stack_b;

	if (argc < 2)
		return (-1);
	input_validation(argc, argv);
	stack_a = (t_stack **)malloc(sizeof(t_stack *));
	stack_b = (t_stack **)malloc(sizeof(t_stack *));
	*stack_a = NULL;
	*stack_b = NULL;
	fill_stack_with_values(argc, argv, stack_a);
	if (stack_sorted(stack_a))
	{
		free_stack(stack_a);
		free_stack(stack_b);
		return (0);
	}
	print_stack(stack_a);
	sleep(15);
	// sort_stack(stack_a, stack_b);
	print_stack(stack_a);
	free_all_stacks(stack_a, stack_b);
	return (0);
}
