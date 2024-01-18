/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:49:01 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/16 18:49:01 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

t_stack	*get_stack_before_bottom(t_stack *stack)
{
	t_stack	*tmp;

	tmp = stack;
	while (tmp->next->next)
		tmp = tmp->next;
	return (tmp);
}

t_stack	*get_stack_bottom(t_stack *stack)
{
	t_stack	*tmp;

	tmp = stack;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_stack	*get_stack_before_top(t_stack *stack)
{
	t_stack	*tmp;

	tmp = stack;
	while (tmp->next->next)
		tmp = tmp->next;
	return (tmp);
}

t_stack	*get_stack_top(t_stack *stack)
{
	t_stack	*tmp;

	tmp = stack;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_stack	*stack_remove_top(t_stack *stack)
{
	t_stack	*tmp;

	if (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
	return (stack);
}
