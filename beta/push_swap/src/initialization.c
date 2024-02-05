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
		new = stack_new(ft_atol(nbr[i]));
		stack_add_bottom(stack_a, new);
		i++;
	}
	if (argc == 2)
		free_argv(nbr);
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

t_stack	*stack_last(t_stack *stack)
{
	if (stack)
	{
		while (stack->next)
			stack = stack->next;
	}
	return (stack);
}
