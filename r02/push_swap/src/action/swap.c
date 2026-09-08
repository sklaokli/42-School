/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 22:37:16 by sklaokli          #+#    #+#             */
/*   Updated: 2026/01/22 15:01:24 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

static void	swap(t_stack **head)
{
	t_stack	*first;
	t_stack	*second;

	if (!head || !*head || !(*head)->next)
		return ;
	first = *head;
	second = first->next;
	first->next = second->next;
	if (first->next)
		first->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	*head = second;
}

void	sa(t_ps *ps)
{
	swap(&ps->a);
	write(1, "sa\n", 3);
}

void	sb(t_ps *ps)
{
	swap(&ps->b);
	write(1, "sb\n", 3);
}

void	ss(t_ps *ps)
{
	swap(&ps->a);
	swap(&ps->b);
	write(1, "ss\n", 3);
}
