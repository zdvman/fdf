/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pivot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:15:22 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/07 13:53:26 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

// Для выбора наиболее оптимального опорного элемента (pivot)
// в контексте быстрой сортировки стеков, одним из лучших подходов
// является использование "медианы трех". Этот метод заключается в выборе
// медианного значения из трех элементов: первого, среднего 
// и последнего в стеке.
// Этот метод помогает уменьшить вероятность выбора крайне неудачного
// опорного элемента, особенно в отсортированных или частично 
// отсортированных данных.

static int	find_median(int first, int middle, int last)
{
	if ((first - middle) * (last - first) >= 0)
		return (first);
	else if ((middle - first) * (last - middle) >= 0)
		return (middle);
	else
		return (last);
}

static int	find_middle(t_stack *stack, int count)
{
	t_stack	*tmp;
	int		middle;
	int		mid_index;

	mid_index = count / 2;
	tmp = stack;
	while (mid_index-- > 0)
		tmp = tmp->next;
	middle = tmp->value;
	return (middle);
}

int	choose_pivot(t_stack *stack)
{
	t_stack	*tmp;
	int		first;
	int		last;
	int		middle;
	int		count;

	if (!stack || !stack->next)
	{
		if (stack)
			return (stack->value);
		else
			return (0);
	}
	tmp = stack;
	first = stack->value;
	count = 1;
	while (tmp->next)
	{
		tmp = tmp->next;
		count++;
	}
	last = tmp->value;
	middle = find_middle(stack, count);
	return (find_median(first, middle, last));
}
