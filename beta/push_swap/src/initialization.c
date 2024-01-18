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

t_stack	*fill_stack_with_values(int argc, char **argv, int i)
{
	t_stack		*stack_a;
	long int	nbr;

	nbr = 0;
	stack_a = NULL;
	while (i < argc)
	{
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
		{
			write(2, "Error\n", 6);
			return (NULL);
		}
		if (i == 1)
			stack_a = stack_new(nbr);
		else
			stack_a = stack_add_bottom(stack_a, nbr);
		i++;
	}
	return (stack_a);
}

t_stack	*stack_new(int value)
{
	t_stack	*new;

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
	t_stack	*tmp;

	new = stack_new(value);
	if (!new)
		return (NULL);
	if (!stack)
		return (new);
	tmp = stack;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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
