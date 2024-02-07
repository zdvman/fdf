/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 06:58:21 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/17 06:58:21 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

// Функция для обмена верхних двух элементов стека A
// flag гарантирует печать названия операции
void	swap_sa(t_stack **stack_a, int flag, int fd)
{
	if (*stack_a && (*stack_a)->next)
	{
		ft_swap(&(*stack_a)->value, &(*stack_a)->next->value);
		if (flag)
			write(fd, "sa\n", 3);
	}
}

// Функция для обмена верхних двух элементов стека B
// flag гарантирует печать названия операции
void	swap_sb(t_stack **stack_b, int flag, int fd)
{
	if (*stack_b && (*stack_b)->next)
	{
		ft_swap(&(*stack_b)->value, &(*stack_b)->next->value);
		if (flag)
			write(fd, "sb\n", 3);
	}
}

// Функция для одновременного обмена верхних двух элементов обоих стеков
// flag равен 0 чтобы печатать только ss
void	swap_ss(t_stack **stack_a, t_stack **stack_b, int fd)
{
	if (*stack_a && (*stack_a)->next && *stack_b && (*stack_b)->next)
	{
		swap_sa(stack_a, 0, 0);
		swap_sb(stack_b, 0, 0);
		write(fd, "ss\n", 3);
	}
}
