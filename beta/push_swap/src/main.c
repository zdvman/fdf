/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:54:18 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/02 17:09:24 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

void print_stack(t_stack *stack)
{
	while (stack)
	{
		printf("%d\n", stack->value);
		stack = stack->next;
	}
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		free_argv_flag;

	stack_a = NULL;
	stack_b = NULL;
	free_argv_flag = 0;
	if (argc < 2 || (argc == 2 && ft_isnumber(argv[1])))
		return (0);
	else if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		free_argv_flag = 1;
	}
	if (!input_validation(argv, !(argc == 2)))
		exit_error(NULL, NULL, argv, free_argv_flag);
	else
	{
		stack_a = fill_stack_with_values(argv_size(argv), argv, !(argc == 2), free_argv_flag);
		sort_stack(&stack_a, &stack_b);
		print_stack(stack_a);
	}
	exit_program(stack_a, NULL, argv, free_argv_flag);
	return (0);
}
