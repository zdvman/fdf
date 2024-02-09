/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:54:18 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/08 20:34:03 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

// static void	print_stack(t_stack **stack)
// {
// 	t_stack	*tmp;
// 	char	*str;

// 	tmp = *stack;
// 	while (tmp)
// 	{
// 		str = ft_itoa(tmp->value);
// 		ft_putstr_fd(str, 1);
// 		tmp = tmp->next;
// 		free(str);
// 		write(1, " ", 1);
// 	}
// 	write(1, "\n", 1);
// 	tmp = *stack;
// 	while (tmp)
// 	{
// 		str = ft_itoa(tmp->index);
// 		ft_putstr_fd(str, 1);
// 		tmp = tmp->next;
// 		free(str);
// 		write(1, " ", 1);
// 	}
// 	write(1, "\n\n", 1);
// }

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
	// print_stack(stack_a);
	sort_stack(stack_a, stack_b);
	// pr int_stack(stack_a);
	free_all_stacks(stack_a, stack_b);
	free(stack_a);
	free(stack_b);
	return (0);
}
