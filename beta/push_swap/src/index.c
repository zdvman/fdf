/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:13:02 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/08 12:13:02 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

static void	index_min_to_max(t_stack **stack)
{
	t_stack	*tmp;
	int		size;
	int		max;

	size = stack_size(stack);
	if (stack && *stack)
	{
		while (size > 0)
		{
			tmp = *stack;
			max = INT_MIN;
			while (tmp)
			{
				if (tmp->value > max && tmp->index == -1)
					max = tmp->value;
				tmp = tmp->next;
			}
			tmp = *stack;
			while (tmp && size > 0)
			{
				if (tmp->value == max)
				{
					tmp->index = --size;
				}
				tmp = tmp->next;
			}
		}
	}
}

void	index_order(t_stack **stack)
{
	t_stack	*tmp;
	int		i;

	tmp = *stack;
	if (stack && *stack)
	{
		i = 0;
		while (tmp)
		{
			tmp->order = i;
			tmp = tmp->next;
			i++;
		}
	}
}

void	index_stack(t_stack **stack)
{
	t_stack	*tmp;

	if (stack && *stack)
	{
		tmp = *stack;
		while (tmp)
		{
			tmp->index = -1;
			tmp = tmp->next;
		}
	}
	index_min_to_max(stack);
	index_order(stack);
}
