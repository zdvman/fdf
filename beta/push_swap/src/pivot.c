/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pivot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:15:22 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/02 14:15:22 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

// Для выбора наиболее оптимального опорного элемента (pivot)
// в контексте быстрой сортировки стеков, одним из лучших подходов
// является использование "медианы трех". Этот метод заключается в выборе
// медианного значения из трех элементов: первого, среднего и последнего в стеке.
// Этот метод помогает уменьшить вероятность выбора крайне неудачного
// опорного элемента, особенно в отсортированных или частично отсортированных данных.

static int	find_median(int first, int middle, int last)
{
	if ((first - middle) * (last - first) >= 0) // Если first больше middle и last
		return (first);
	else if ((middle - first) * (last - middle) >= 0) // Если middle больше first и last
		return (middle);
	else // Если last больше first и middle
		return (last);
}

static int	find_middle(t_stack *stack, int count)
{
	t_stack	*tmp;
	int		middle;
	int		midIndex;

	midIndex = count / 2;
	tmp = stack;
	while (midIndex-- > 0)
		tmp = tmp->next;
	middle = tmp->value;
	return (middle);
}

int	choose_pivot(t_stack *stack)
{
	t_stack	*tmp; 
	int		first;				// Первый элемент
	int		last;				// Последний элемент
	int		middle;				// Средний элемент
	int		count;
	
	if (!stack || !stack->next)
	{
		if (stack)
			return (stack->value);
		else
			return (0);
	}
	tmp = stack;
	first = stack->value; // Первый элемент
	count = 1;			// Счетчик для определения среднего элемента
	while (tmp->next)
	{
		tmp = tmp->next;
		count++;
	}
	last = tmp->value; // Записываем значение последнего элемента
	middle = find_middle(stack, count); // Находим средний элемент
	return find_median(first, middle, last); // Возвращаем медиану из трех значений
}
