/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:32:47 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/07 18:07:09 by dzuiev           ###   ########.fr       */
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

static void	radix_sort(t_stack **stack_a, t_stack **stack_b, int fd)
{
	t_stack	**tmp;
	int	i, j;
	int	s;

	i = 10;
	if (!stack_a || !*stack_a || !stack_b)
		return ;
	tmp = stack_a;
	s = stack_size(stack_a);
	while (!stack_sorted(tmp))
	{
		j = 0;
		while (*tmp)
		{
			if ((*tmp)->value % i == j)
			{
				while ((*tmp)->prev)
				{
					if ((*tmp)->index < s / 2)
						rotate_ra(stack_a, 1, fd);
					else
						reverse_rotate_rra(stack_a, 1, fd);
				}
				swap_sa(stack_a, 1, fd);
				push_pb(stack_a, stack_b, fd);
			}
			if ((*tmp)->index == s)
			{
				j++;
				s = stack_size(stack_a);
				index_stack(stack_a);
			}
			if (j == 9)
			{
				j = 0;
				i *= 10;
			}
		}
		while (*stack_b)
			push_pa(stack_a, stack_b, fd);
	}
}

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
