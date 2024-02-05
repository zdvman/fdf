/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:17:52 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/05 18:47:24 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../../libft/libft.h"

typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
}					t_stack;

void	input_validation(int argc, char **argv);
void	exit_error(t_stack **stack_a, t_stack **stack_b);
void	free_all_stacks(t_stack **stack_a, t_stack **stack_b);
void	free_stack(t_stack **stack);
void	free_argv(char **argv);
void	fill_stack_with_values(int argc, char **argv, t_stack **stack);
void	stack_add_bottom(t_stack **stack, t_stack *new);
t_stack	*stack_new(int value);
t_stack	*stack_last(t_stack *stack);
int		stack_size(t_stack **stack);
void	swap_sa(t_stack **stack_a, int flag);
void	swap_sb(t_stack **stack_b, int flag);
void	swap_ss(t_stack **stack_a, t_stack **stack_b);
void	push_pa(t_stack **stack_a, t_stack **stack_b);
void	push_pb(t_stack **stack_a, t_stack **stack_b);
void	rotate_ra(t_stack **stack_a, int flag);
void	rotate_rb(t_stack **stack_b, int flag);
void	rotate_rr(t_stack **stack_a, t_stack **stack_b);
void	reverse_rotate_rra(t_stack **stack_a, int flag);
void	reverse_rotate_rrb(t_stack **stack_b, int flag);
void	reverse_rotate_rrr(t_stack **stack_a, t_stack **stack_b);
void	sort_stack(t_stack **stack_a, t_stack **stack_b);
int		stack_sorted(t_stack **stack);
int		choose_pivot(t_stack *stack);

#endif
