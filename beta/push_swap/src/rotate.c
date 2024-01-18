/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 07:11:06 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/17 07:11:06 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

void rotate_ra(t_stack *stack_a, int flag)
{
	t_stack	*tmp;
	t_stack	*tmp2;

	if (stack_a && stack_a->next)
	{
		tmp = stack_a;
		tmp2 = stack_a;
		while (tmp->next)
			tmp = tmp->next;
		stack_a = stack_a->next;
		tmp->next = tmp2;
		tmp2->next = NULL;
		if (flag)
			ft_putstr("ra\n");
	}
}

void rotate_rb(t_stack *stack_b, int flag)
{
	t_stack	*tmp;
	t_stack	*tmp2;

	if (stack_b && stack_b->next)
	{
		tmp = stack_b;
		tmp2 = stack_b;
		while (tmp->next)
			tmp = tmp->next;
		stack_b = stack_b->next;
		tmp->next = tmp2;
		tmp2->next = NULL;
		if (flag)
			ft_putstr("rb\n");
	}
}

void rotate_rr(t_stack *stack_a, t_stack *stack_b)
{
	rotate_ra(stack_a, 0);
	rotate_rb(stack_b, 0);
	ft_putstr("rr\n");
}
