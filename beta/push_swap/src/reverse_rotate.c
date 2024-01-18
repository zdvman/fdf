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

void reverse_rotate_rra(t_stack *stack_a, int flag)
{
	t_stack	*tmp;
	t_stack	*tmp2;

	if (stack_a && stack_a->next)
	{
		tmp = stack_a;
		while (tmp->next->next)
			tmp = tmp->next;
		tmp2 = tmp->next;
		tmp->next = NULL;
		tmp2->next = stack_a;
		stack_a = tmp2;
		if (flag)
			ft_putstr("rra\n");
	}
}

void reverse_rotate_rrb(t_stack *stack_b, int flag)
{
	t_stack	*tmp;
	t_stack	*tmp2;

	if (stack_b && stack_b->next)
	{
		tmp = stack_b;
		while (tmp->next->next)
			tmp = tmp->next;
		tmp2 = tmp->next;
		tmp->next = NULL;
		tmp2->next = stack_b;
		stack_b = tmp2;
		if (flag)
			ft_putstr("rrb\n");
	}
}

void reverse_rotate_rrr(t_stack *stack_a, t_stack *stack_b)
{
	reverse_rotate_rra(stack_a, 0);
	reverse_rotate_rrb(stack_b, 0);
	ft_putstr("rrr\n");
}