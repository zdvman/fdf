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

void	swap_sa(t_stack *stack_a, int flag)
{
	if (stack_a && stack_a->next)
	{
		ft_swap(&stack_a->value, &stack_a->next->value);
		if (flag)
			ft_putstr("sa\n");
	}
}

void	swap_sb(t_stack *stack_b, int flag)
{
	if (stack_b && stack_b->next)
	{
		ft_swap(&stack_b->value, &stack_b->next->value);
		if (flag)
			ft_putstr("sb\n");
	}
}

void	swap_ss(t_stack *stack_a, t_stack *stack_b)
{
	swap_sa(stack_a, 0);
	swap_sb(stack_b, 0);
	ft_putstr("ss\n");
}
