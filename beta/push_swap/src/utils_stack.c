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

// функция освобождения памяти выделенной для стека
// Использование указателя на указатель (t_stack **stack)
// в функции free_stack позволяет напрямую изменять значение указателя,
// который передается в функцию. Это необходимо, если мы хотим изменить
// значение самого внешнего указателя (в данном случае указателя
// на начало списка) в вызывающей функции, а не только локальную копию
// этого указателя внутри free_stack.
void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

// stack_sorted проверяет, отсортирован ли стек в порядке возрастания
// Проверяем, не является ли стек пустым
// Перебираем элементы стека до предпоследнего
// Если текущее значение больше следующего, стек не отсортирован
// Переходим к следующему элементу стека
// Возвращаем 1, если стек пуст или отсортирован
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

// Функция stack_size подсчитывает количество элементов в стеке
// Инициализация счетчика размера стека
// Использование временной переменной для итерации по стеку
// Условие выхода их цикла (пока не достигнем конца стека)
// Увеличиваем счетчик для каждого элемента стека
// Переходим к следующему элементу
// Возвращаем итоговый размер стека
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

// Функция duplicates_found проверяет наличие дубликатов в стеке
// Проверяем, не пуст ли стек
// Итерация по каждому элементу стека
// Используем tmp для внутренней итерации
// Проходим по оставшимся элементам стека
// Если найдено совпадение, возвращаем 1
// Переходим к следующему элементу для проверки
// Если дубликатов нет, возвращаем 0
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
