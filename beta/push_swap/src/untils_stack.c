/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untils_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:02:00 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/21 17:02:00 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

void	free_stack(t_stack *stack)
{
	t_stack	*tmp;

	if (!stack)
		return ;
	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}

int	stack_sorted(t_stack *stack)
{
	if (stack)
	{
		while (stack->next)
		{
			if (stack->value > stack->next->value)
				return (0);
			stack = stack->next;
		}
	}
	return (1);
}

int	stack_size(t_stack *stack)
{
	int		size;
	t_stack	*tmp;

	size = 0;
	tmp = stack;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

int	duplicates_found(t_stack *stack)
{
	t_stack	*tmp;

	tmp = NULL;
	if (stack)
	{
		while (stack->next)
		{
			tmp = stack;
			while (tmp->next)
			{
				tmp = tmp->next;
				if (stack->value == tmp->value)
					return (1);
			}
			stack = stack->next;
		}
	}
	return (0);
}
