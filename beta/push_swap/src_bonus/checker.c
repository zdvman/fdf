/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:47:19 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/11 17:44:42 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Функция: checker_result                                                  */
/*   Описание: Проверяет, отсортирован ли стек A и пуст ли стек B. Выводит    */
/*   "OK", если стек A отсортирован и стек B пуст, иначе выводит "KO".        */
/*   Параметры:                                                               */
/*     - t_stack **stack_a: Указатель на указатель на вершину стека A.        */
/*     - t_stack **stack_b: Указатель на указатель на вершину стека B.        */
/*   Возвращает: Не возвращает значения.                                      */
/*                                                                            */
/* ************************************************************************** */

static void	checker_result(t_stack **stack_a, t_stack **stack_b)
{
	if (stack_sorted(stack_a) && *stack_b == NULL)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция: check_commands                                                  */
/*   Описание: Считывает команды с стандартного ввода и выполняет их на       */
/*   стеках A и B. Если команда не выполнена, завершает программу с ошибкой.  */
/*   Параметры:                                                               */
/*     - t_stack **stack_a: Указатель на указатель на вершину стека A.        */
/*     - t_stack **stack_b: Указатель на указатель на вершину стека B.        */
/*   Возвращает: Не возвращает значения.                                      */
/*                                                                            */
/* ************************************************************************** */

static void	check_commands(t_stack **stack_a, t_stack **stack_b)
{
	char	*command;

	command = get_next_line(0);
	while (command != NULL)
	{
		if (execute_commands(stack_a, stack_b, command))
		{
			free(command);
			exit_error(stack_a, stack_b);
		}
		free(command);
		command = get_next_line(0);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция: main                                                            */
/*   Описание: Главная функция программы. Проверяет аргументы, инициализирует */
/*   стеки, выполняет команды для сортировки и проверяет результат.           */
/*   Параметры:                                                               */
/*     - int argc: Количество аргументов командной строки.                    */
/*     - char **argv: Массив аргументов командной строки.                     */
/*   Возвращает: 0 при успешном завершении или -1 при ошибке.                 */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	t_stack	**stack_a;
	t_stack	**stack_b;

	if (argc < 2)
		return (-1);
	input_validation(argc, argv);
	stack_a = (t_stack **)malloc(sizeof(t_stack *));
	stack_b = (t_stack **)malloc(sizeof(t_stack *));
	*stack_a = NULL;
	*stack_b = NULL;
	fill_stack_with_values(argc, argv, stack_a);
	if (stack_sorted(stack_a))
	{
		free_all_stacks(stack_a, stack_b);
		free(stack_a);
		free(stack_b);
		return (0);
	}
	check_commands(stack_a, stack_b);
	checker_result(stack_a, stack_b);
	free_all_stacks(stack_a, stack_b);
	free(stack_a);
	free(stack_b);
	return (0);
}
