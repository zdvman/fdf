/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:32:47 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/06 22:34:07 by dzuiev           ###   ########.fr       */
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


static void radix_sort(t_stack **stack_a, t_stack **stack_b, int size, int fd)
{
	int		pivot;
	int		i;
	int		j;
	int		*arr;
	t_stack	*tmp;

	i = 0;
	j = 0;
	arr = (int *)malloc(sizeof(int) * size);
	tmp = *stack_a;
	while (tmp)
	{
		arr[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
	pivot = choose_pivot(*stack_a);
	while (stack_size(stack_a) > 3)
	{
		i = 0;
		while (i < size)
		{
			if (arr[i] < pivot)
			{
				push_pb(stack_a, stack_b, fd);
				j++;
			}
			else
				rotate_ra(stack_a, 1, fd);
			i++;
		}
		while (j > 0)
		{
			push_pa(stack_a, stack_b, fd);
			j--;
		}
	}
	tiny_sort(stack_a, stack_size(stack_a), fd);
	while (*stack_b)
		push_pa(stack_a, stack_b, fd);
	free(arr);
}

static int	file_open(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		write(1, "Error: file open failed\n", 24);
		exit(1);
	}
	return (fd);
}

static int	file_open_old(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY, 0644);
	if (fd < 0)
	{
		write(1, "Error: file open failed\n", 24);
		exit(1);
	}
	return (fd);
}

void	sort_stack(t_stack **stack_a, t_stack **stack_b)
{
	int fd;
	int	size;
	int size2 = stack_size(stack_b);
	char *line;

	fd = file_open("commands.txt");
	size = stack_size(stack_a);
	size2++;
	if (size <= 3)
	{
		tiny_sort(stack_a, size, fd);
	}
	else
	{
		radix_sort(stack_a, stack_b, size, fd);
	}
		close(fd);
		// fsync(fd);
		fd = file_open_old("commands.txt");
		line = get_next_line(fd);
		ft_putstr(line);
		free(line);
		close(fd);
}
