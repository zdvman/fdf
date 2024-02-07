/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 07:30:55 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/17 07:30:55 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

// Функция для выполнения обратного вращения стека A
// flag гарантирует печать названия операции
void	reverse_rotate_rra(t_stack **stack_a, int flag, int fd)
{
	t_stack	*tmp;
	t_stack	*tmp2;

	if (stack_a && *stack_a && (*stack_a)->next)
	{
		tmp = *stack_a;
		while (tmp->next->next)
			tmp = tmp->next;
		tmp2 = tmp->next;
		tmp->next = NULL;
		tmp2->next = *stack_a;
		*stack_a = tmp2;
		if (flag)
			write(fd, "rra\n", 4);
	}
}

// Функция для выполнения обратного вращения стека B
// flag гарантирует печать названия операции
void	reverse_rotate_rrb(t_stack **stack_b, int flag, int fd)
{
	t_stack	*tmp;
	t_stack	*tmp2;

	if (stack_b && *stack_b && (*stack_b)->next)
	{
		tmp = *stack_b;
		while (tmp->next->next)
			tmp = tmp->next;
		tmp2 = tmp->next;
		tmp->next = NULL;
		tmp2->next = *stack_b;
		*stack_b = tmp2;
		if (flag)
			write(fd, "rrb\n", 4);
	}
}

// Функция для одновременного выполнения обратного вращения обоих стеков
// flag равен 0 чтобы печатать только rrr
void	reverse_rotate_rrr(t_stack **stack_a, t_stack **stack_b, int fd)
{
	if (stack_a && *stack_a && (*stack_a)->next
		&& stack_b && *stack_b && (*stack_b)->next)
	{
		reverse_rotate_rra(stack_a, 0, 0);
		reverse_rotate_rrb(stack_b, 0, 0);
		write(fd, "rrr\n", 4);
	}
}
