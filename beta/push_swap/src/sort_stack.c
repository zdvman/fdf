/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:32:47 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/21 19:32:47 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

static void quicksort_stack_b(t_stack **stack_b, t_stack **stack_a, int count) {
    if (count <= 1) return;

    while (count--) {
        push_pa(stack_a, stack_b);
    }
}

static void quicksort_stack_a(t_stack **stack_a, t_stack **stack_b, int count) {
    if (count <= 1) return;

    int pivot = choose_pivot(*stack_a);
    int pushed_to_b = 0;

    for (int i = 0; i < count; ++i) {
        if ((*stack_a)->value < pivot) {
            push_pb(stack_a, stack_b);
            pushed_to_b++;
        } else {
            rotate_ra(stack_a, 1);
        }
    }

    // Перемещаем элементы обратно в stack_a перед рекурсивной сортировкой оставшейся части
    for (int i = 0; i < count - pushed_to_b; ++i) {
        reverse_rotate_rra(stack_a, 1);
    }

    quicksort_stack_a(stack_a, stack_b, count - pushed_to_b);
    quicksort_stack_b(stack_b, stack_a, pushed_to_b);
}

void sort_stack(t_stack **stack_a, t_stack **stack_b) {
    int count = stack_size(stack_a);
    quicksort_stack_a(stack_a, stack_b, count);
}

// void sort_stack(t_stack **stack_a, t_stack **stack_b)
// {
// 	int	count = stack_size(*stack_a);
// 	if (count == 2)
// 	{
// 		if ((*stack_a)->value > (*stack_a)->next->value)
// 		{
// 			swap_sa(stack_a, 1);
// 		}
// 		return ;
// 	}
// 	quicksort_stack_a(stack_a, stack_b, count);
// }
