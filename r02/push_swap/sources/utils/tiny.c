/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:47:21 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 03:24:49 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_stack **a, t_stack **b)
{
	push_swap(a, b, SA, false);
}

void	sort_three(t_stack **a, t_stack **b)
{
	t_stack	*max;

	max = find_max(*a);
	if (*a == max)
		push_swap(a, b, RA, false);
	if ((*a)->next == max)
		push_swap(a, b, RRA, false);
	if ((*a)->value > (*a)->next->value)
		push_swap(a, b, SA, false);
}

void	sort_four(t_stack **a, t_stack **b)
{
	bring_to_top(a, find_min(*a), A);
	push_swap(a, b, PB, false);
	sort_three(a, b);
	push_swap(a, b, PA, false);
}

void	sort_five(t_stack **a, t_stack **b)
{
	bring_to_top(a, find_min(*a), A);
	push_swap(a, b, PB, false);
	bring_to_top(a, find_min(*a), A);
	push_swap(a, b, PB, false);
	sort_three(a, b);
	push_swap(a, b, PA, false);
	push_swap(a, b, PA, false);
}

void	tiny_sort(t_data *stack)
{
	if (stack->size == 2)
		sort_two(&stack->a, &stack->b);
	else if (stack->size == 3)
		sort_three(&stack->a, &stack->b);
	else if (stack->size == 4)
		sort_four(&stack->a, &stack->b);
	else if (stack->size == 5)
		sort_five(&stack->a, &stack->b);
}
