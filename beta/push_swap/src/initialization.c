/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:04:35 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/09 13:09:42 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Функция `fill_stack_with_values` заполняет стек значениями из аргументов */
/*   командной строки. Эти значения могут быть представлены как одной строкой */
/*   с разделителями-пробелами (если аргументов два), так и отдельными        */
/*   аргументами (если их больше двух).                                       */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `argc`: количество аргументов командной строки.                        */
/*   - `argv`: значения аргументов командной строки.                          */
/*   - `stack_a`: двойной указатель на начало стека `a`.                      */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Если аргументов два, используется `ft_split` для разбиения строки на  */
/*      отдельные числа.                                                      */
/*   2. Если аргументов больше двух, используются аргументы                   */
/*      начиная с `argv[1]`.                                                  */
/*   3. Для каждого числа создается новый элемент стека с помощью `stack_new` */
/*      и добавляется в низ стека с помощью `stack_add_bottom`.               */
/*   4. После заполнения стека вызывается `index_stack` для назначения        */
/*      индексов.                                                             */
/*   5. Если был использован `ft_split`, выделенная память освобождается.     */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Функция не возвращает значение.                                        */
/*                                                                            */
/* ************************************************************************** */

void	fill_stack_with_values(int argc, char **argv, t_stack **stack_a)
{
	t_stack	*new;
	char	**nbr;
	int		i;

	i = 0;
	new = NULL;
	if (argc == 2)
		nbr = ft_split(argv[1], ' ');
	else
	{
		nbr = argv;
		i = 1;
	}
	while (nbr[i])
	{
		new = stack_new(ft_atoi(nbr[i]));
		stack_add_bottom(stack_a, new);
		i++;
	}
	index_stack(stack_a);
	if (argc == 2)
		free_argv(nbr);
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция `stack_new` создает новый элемент стека с заданным значением.    */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `value`: значение для нового элемента стека.                           */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Выделение памяти под новый элемент стека.                             */
/*   2. Если память не выделена, возвращается `NULL`.                         */
/*   3. Инициализация значения элемента стека и указателя на следующий        */
/*      элемент.                                                              */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Возвращает указатель на новый элемент стека или `NULL` при ошибке.     */
/*                                                                            */
/* ************************************************************************** */

t_stack	*stack_new(int value)
{
	t_stack	*new;

	new = NULL;
	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция `stack_add_bottom` добавляет новый элемент в конец стека.        */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `stack`: двойной указатель на начало стека.                            */
/*   - `new`: указатель на новый элемент для добавления.                      */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Проверка, что оба указателя не `NULL`.                                */
/*   2. Если стек не пуст, поиск последнего элемента с помощью `stack_last`   */
/*      и добавление нового элемента после него.                              */
/*   3. Если стек пуст, новый элемент становится началом стека.               */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Функция не возвращает значение.                                        */
/*                                                                            */
/* ************************************************************************** */

void	stack_add_bottom(t_stack **stack, t_stack *new)
{
	t_stack	*last;

	if (stack && new)
	{
		if (*stack)
		{
			last = stack_last(*stack);
			last->next = new;
		}
		else
			*stack = new;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция `stack_last` возвращает последний элемент стека.                 */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `stack`: указатель на начало стека.                                    */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Проверка, что стек не пуст.                                           */
/*   2. Проход по стеку до последнего элемента.                               */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Возвращает указатель на последний элемент стека или `NULL`, если стек  */
/*     пуст.                                                                  */
/*                                                                            */
/* ************************************************************************** */

t_stack	*stack_last(t_stack *stack)
{
	if (stack)
	{
		while (stack->next)
			stack = stack->next;
	}
	return (stack);
}
