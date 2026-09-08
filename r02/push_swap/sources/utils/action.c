/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:44:11 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/16 15:15:43 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack **a, t_stack **b, t_action action)
{
	t_stack	*tmp;

	if (action == SA)
	{
		if (*a && (*a)->next)
		{
			tmp = (*a)->next->next;
			(*a)->next->next = *a;
			*a = (*a)->next;
			(*a)->next->next = tmp;
		}
	}
	if (action == SB)
	{
		if (*b && (*b)->next)
		{
			tmp = (*b)->next->next;
			(*b)->next->next = *b;
			*b = (*b)->next;
			(*b)->next->next = tmp;
		}
	}
}

void	push(t_stack **a, t_stack **b, t_action action)
{
	t_stack	*tmp;

	if (action == PA)
	{
		if (*b)
		{
			tmp = *a;
			*a = *b;
			*b = (*b)->next;
			(*a)->next = tmp;
		}
	}
	if (action == PB)
	{
		if (*a)
		{
			tmp = *b;
			*b = *a;
			*a = (*a)->next;
			(*b)->next = tmp;
		}
	}
}

void	rotate(t_stack **a, t_stack **b, t_action action)
{
	t_stack	*tmp;

	if (action == RA || action == RR)
	{
		if (*a && (*a)->next)
		{
			tmp = last_node(*a);
			tmp->next = *a;
			*a = (*a)->next;
			tmp->next->next = NULL;
		}
	}
	if (action == RB || action == RR)
	{
		if (*b && (*b)->next)
		{
			tmp = last_node(*b);
			tmp->next = *b;
			*b = (*b)->next;
			tmp->next->next = NULL;
		}
	}
}

void	rev_rotate(t_stack **a, t_stack **b, t_action action)
{
	t_stack	*tmp;

	if (action == RRA || action == RRR)
	{
		if (*a && (*a)->next)
		{
			tmp = *a;
			while (tmp->next->next)
				tmp = tmp->next;
			tmp->next->next = *a;
			*a = tmp->next;
		}
	}
	if (action == RRB || action == RRR)
	{
		if (*b && (*b)->next)
		{
			tmp = *b;
			while (tmp->next->next)
				tmp = tmp->next;
			tmp->next->next = *b;
			*b = tmp->next;
		}
	}
	tmp->next = NULL;
}

void	push_swap(t_stack **a, t_stack **b, t_action action, bool checker)
{
	if (!checker)
		print_action(action);
	if (action == SA || action == SB)
		swap(a, b, action);
	else if (action == PA || action == PB)
		push(a, b, action);
	else if (action == RA || action == RB || action == RR)
		rotate(a, b, action);
	else if (action == RRA || action == RRB || action == RRR)
		rev_rotate(a, b, action);
}
