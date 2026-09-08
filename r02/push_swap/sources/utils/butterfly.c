/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   butterfly.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 00:16:17 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 03:24:49 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_butterfly(t_stack **a, t_stack **b)
{
	while (*b)
	{
		bring_to_top(b, find_max(*b), B);
		push_swap(a, b, PA, false);
	}
}

void	do_butterfly(t_stack **a, t_stack **b, int size)
{
	int	counter;

	counter = 1;
	while (*a)
	{
		if ((int)(*a)->index <= counter)
		{
			push_swap(a, b, PB, false);
			push_swap(a, b, RB, false);
			counter++;
		}
		else if ((int)(*a)->index <= counter + size)
		{
			push_swap(a, b, PB, false);
			counter++;
		}
		else
			push_swap(a, b, RA, false);
	}
}

int	get_butterfy_size(int size)
{
	if (size < 50)
		return (3 + (size - 6) / 7);
	else if (size >= 50 && size < 100)
		return (10 + (size - 50) / 8);
	else if (size >= 100 && size < 350)
		return (18 + (size - 100) / 9);
	else if (size >= 350 && size <= 500)
		return (27 + (size - 350) / 15);
	return (37 + (size - 500) / 20);
}

void	butterfly_sort(t_data *stack)
{
	int	size;

	size = get_butterfy_size(stack->size);
	do_butterfly(&stack->a, &stack->b, size);
	sort_butterfly(&stack->a, &stack->b);
}
