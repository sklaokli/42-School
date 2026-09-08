/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 22:26:43 by sklaokli          #+#    #+#             */
/*   Updated: 2026/01/20 22:48:13 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

static void	rotate(t_stack **head)
{
	t_stack	*first;
	t_stack	*last;

	if (!head || !*head || !(*head)->next)
		return ;
	first = *head;
	last = stack_last(*head);
	*head = first->next;
	(*head)->prev = NULL;
	first->next = NULL;
	first->prev = last;
	last->next = first;
}

void	ra(t_ps *ps)
{
	rotate(&ps->a);
	write(1, "ra\n", 3);
}

void	rb(t_ps *ps)
{
	rotate(&ps->b);
	write(1, "rb\n", 3);
}

void	rr(t_ps *ps)
{
	rotate(&ps->a);
	rotate(&ps->b);
	write(1, "rr\n", 3);
}
