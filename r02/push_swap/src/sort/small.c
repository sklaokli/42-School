/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 23:40:08 by sklaokli          #+#    #+#             */
/*   Updated: 2026/01/22 15:03:05 by sklaokli         ###   ########.fr       */
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
