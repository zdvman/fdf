/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:15:25 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/10 15:38:14 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

static int	do_reverse(t_stack **stack_a, t_stack **stack_b, char *command)
{
	if (!ft_strcmp(command, "rra"))
	{
		reverse_rotate_rra(stack_a, 1, 1);
		return (0);
	}
	else if (!ft_strcmp(command, "rrb"))
	{
		reverse_rotate_rrb(stack_b, 1, 1);
		return (0);
	}
	else if (!ft_strcmp(command, "rrr"))
	{
		reverse_rotate_rrr(stack_a, stack_b, 1);
		return (0);
	}
	else
		return (1);
}

static int	do_rotate(t_stack **stack_a, t_stack **stack_b, char *command)
{
	if (!ft_strcmp(command, "ra"))
	{
		rotate_ra(stack_a, 1, 1);
		return (0);
	}
	else if (!ft_strcmp(command, "rb"))
	{
		rotate_rb(stack_b, 1, 1);
		return (0);
	}
	else if (!ft_strcmp(command, "rr"))
	{
		rotate_rr(stack_a, stack_b, 1);
		return (0);
	}
	else
		return (1);
}

static int	do_push(t_stack **stack_a, t_stack **stack_b, char *command)
{
	if (!ft_strcmp(command, "pa"))
	{
		push_pa(stack_a, stack_b, 1);
		return (0);
	}
	else if (!ft_strcmp(command, "pb"))
	{
		push_pb(stack_a, stack_b, 1);
		return (0);
	}
	else
		return (1);
}

static int	do_swap(t_stack **stack_a, t_stack **stack_b, char *command)
{
	if (!ft_strcmp(command, "sa"))
	{
		swap_sa(stack_a, 1, 1);
		return (0);
	}
	else if (!ft_strcmp(command, "sb"))
	{
		swap_sb(stack_b, 1, 1);
		return (0);
	}
	else if (!ft_strcmp(command, "ss"))
	{
		swap_ss(stack_a, stack_b, 1);
		return (0);
	}
	else
		return (1);
}

int	execute_commands(t_stack **stack_a, t_stack **stack_b, char *command)
{
	return (do_swap(stack_a, stack_b, command) || do_push(stack_a, stack_b, command)
	      || do_rotate(stack_a, stack_b, command) || do_reverse(stack_a, stack_b, command));
}
