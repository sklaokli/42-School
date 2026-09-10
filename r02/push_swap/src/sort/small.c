/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 23:40:08 by sklaokli          #+#    #+#             */
/*   Updated: 2026/09/10 21:35:05 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static size_t	get_index(t_stack *stack)
{
	if (!stack)
		return (0);
	return (((t_nbr *)stack->content)->index);
}

void	sort_two(t_ps *ps)
{
	size_t	first;
	size_t	second;

	first = get_index(ps->a);
	second = get_index(ps->a->next);
	if (first > second)
		sa(ps);
}

void	sort_three(t_ps *ps)
{
	size_t	first;
	size_t	second;
	size_t	third;

	first = get_index(ps->a);
	second = get_index(ps->a->next);
	third = get_index(ps->a->next->next);
	if (first > second && first > third)
		ra(ps);
	else if (second > first && second > third)
		rra(ps);
	if (get_index(ps->a) > get_index(ps->a->next))
		sa(ps);
}

static void	push_min_to_b(t_ps *ps, size_t min_idx)
{
	size_t	pos;
	size_t	size;
	t_stack	*cur;

	pos = 0;
	cur = ps->a;
	while (cur && ((t_nbr *)cur->content)->index != min_idx)
	{
		pos++;
		cur = cur->next;
	}
	size = stack_size(ps->a);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ra(ps);
	}
	else
	{
		while (pos++ < size)
			rra(ps);
	}
	pb(ps);
}

void	sort_five(t_ps *ps, size_t size)
{
	size_t	min_idx;

	min_idx = 0;
	while (size > 3)
	{
		push_min_to_b(ps, min_idx++);
		size--;
	}
	sort_three(ps);
	while (min_idx > 0)
	{
		pa(ps);
		min_idx--;
	}
}
