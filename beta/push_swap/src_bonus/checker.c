/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:47:19 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/10 15:31:20 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

static void	checker_result(t_stack **stack_a, t_stack **stack_b)
{
	if (stack_sorted(stack_a) && *stack_b == NULL)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

static void	check_commands(t_stack **stack_a, t_stack **stack_b, int fd)
{
	char	*command;

	command = get_next_line(fd);
	while (command != NULL)
	{
		if (execute_commands(stack_a, stack_b, command))
		{
			free(command);
			exit_error(stack_a, stack_b) ;
		}
		free(command);
		command = get_next_line(fd);
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
		free_all_stacks(stack_a, stack_b);
		free(stack_a);
		free(stack_b);
		return (0);
	}
	check_commands(stack_a, stack_b, 0);
	checker_result(stack_a, stack_b);
	free_all_stacks(stack_a, stack_b);
	free(stack_a);
	free(stack_b);
	return (0);
}
