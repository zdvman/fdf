/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:04:35 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/16 17:04:35 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

t_stack	*fill_stack_with_values(int argc, char **argv,
			int i, int free_argv_flag)
{
	t_stack		*stack_a;
	long int	nbr;
	int			j;

	nbr = 0;
	j = i;
	stack_a = NULL;
	while (i < argc)
	{
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			exit_error(stack_a, NULL, argv, free_argv_flag);
		if (i == j)
			stack_a = stack_new(nbr);
		else
			stack_a = stack_add_bottom(stack_a, nbr);
		i++;
	}
	if (duplicates_found(stack_a))
		exit_error(stack_a, NULL, argv, free_argv_flag);
	return (stack_a);
}

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

t_stack	*stack_add_bottom(t_stack *stack, int value)
{
	t_stack	*new;
	t_stack	*last;

	new = stack_new(value);
	if (!new)
		return (NULL);
	if (stack)
	{
		last = stack_last(stack);
		last->next = new;
	}
	else
		stack = new;
	return (stack);
}

t_stack	*stack_add_top(t_stack *stack, int value)
{
	t_stack	*new;

	new = stack_new(value);
	if (!new)
		return (NULL);
	if (!stack)
		return (new);
	new->next = stack;
	return (new);
}

t_stack	*stack_last(t_stack *stack)
{
	if (stack)
	{
		while (stack->next)
			stack = stack->next;
	}
	return (stack);
}
