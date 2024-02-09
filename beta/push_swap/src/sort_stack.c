/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:32:47 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/09 11:01:09 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_push_swap.h"

static void	sort_three(t_stack **stack_a, int fd)
{
	if ((*stack_a)->value < (*stack_a)->next->value)
	{
		if ((*stack_a)->value > (*stack_a)->next->next->value)
			reverse_rotate_rra(stack_a, 1, fd);
		else
		{
			swap_sa(stack_a, 1, fd);
			rotate_ra(stack_a, 1, fd);
		}
	}
	else
	{
		if ((*stack_a)->next->value > (*stack_a)->next->next->value)
		{
			swap_sa(stack_a, 1, fd);
			reverse_rotate_rra(stack_a, 1, fd);
		}
		else if ((*stack_a)->value < (*stack_a)->next->next->value)
			swap_sa(stack_a, 1, fd);
		else
			rotate_ra(stack_a, 1, fd);
	}
}

static void	tiny_sort(t_stack **stack_a, int size, int fd)
{
	if (stack_a && *stack_a && size == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			swap_sa(stack_a, 1, fd);
	}
	else if (stack_a && *stack_a && size == 3)
		sort_three(stack_a, fd);
}

static int	get_max_steps(t_stack **stack)
{
	t_stack	*head;
	int		max;
	int		max_bits;

	head = *stack;
	max = head->index;
	max_bits = 0;
	while (head)
	{
		if (head->index > max)
			max = head->index;
		head = head->next;
	}
	while ((max >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

static void	radix_sort(t_stack **stack_a, t_stack **stack_b, int fd)
{
	int	i;
	int	j;
	int	max_bits;
	int	current_size;

	i = 0;
	max_bits = get_max_steps(stack_a);
	while (i < max_bits)
	{
		j = 0;
		current_size = stack_size(stack_a);
		while (j < current_size)
		{
			if ((((*stack_a)->index >> i) & 1) == 1)
				rotate_ra(stack_a, 1, fd);
			else
				push_pb(stack_a, stack_b, fd);
			j++;
		}
		while (stack_size(stack_b) != 0)
			push_pa(stack_a, stack_b, fd);
		i++;
	}
}
/*
static void	sort_by_index(t_stack **stack_a, t_stack **stack_b, int fd)
{
	t_stack *tmp;
	int		median;
	int		i;
	int		j;
	int		k;

	k = 0;
	j = 10;
	while (stack_sorted(stack_a) == 0)
	{
		i = 0;
		tmp = *stack_a;
		median = stack_size(stack_a) / 2;
		while (*stack_a && i < 10)
		{
			if (tmp == NULL)
			{
				i++;
				tmp = *stack_a;
				median = stack_size(stack_a) / 2;
			}
			else if (tmp->index % j == i)
			{
				k = tmp->order;
				if (k <= median)
				{
					while (k-- > 0)
						rotate_ra(stack_a, 1, fd);
				}
				else
				{
					while (k++ < stack_size(stack_a))
						reverse_rotate_rra(stack_a, 1, fd);
				}
				push_pb(stack_a, stack_b, fd);
				index_order(stack_a);
				median = stack_size(stack_a) / 2;
				tmp = *stack_a;
			}
			else
			{
				tmp = tmp->next;
			}
		}
		j *= 10;
		while (stack_size(stack_b) != 0)
			push_pa(stack_a, stack_b, fd);
	}
}

*/

void	sort_stack(t_stack **stack_a, t_stack **stack_b)
{
	int		fd;
	int		size;
	char	*line;

	fd = file_open("commands.txt");
	size = stack_size(stack_a);
	if (size <= 3)
	{
		tiny_sort(stack_a, size, fd);
	}
	else
	{
		// sort_by_index(stack_a, stack_b, fd);
		radix_sort(stack_a, stack_b, fd);
	}
	close(fd);
	fd = file_open_old("commands.txt");  
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_putstr_fd(line, 1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
