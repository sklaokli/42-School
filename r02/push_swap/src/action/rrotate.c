/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 22:32:16 by sklaokli          #+#    #+#             */
/*   Updated: 2026/01/22 15:55:32 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

static void	reverse_rotate(t_stack **head)
{
	t_stack	*last;
	t_stack	*second_last;

	if (!head || !*head || !(*head)->next)
		return ;
	last = stack_last(*head);
	second_last = last->prev;
	second_last->next = NULL;
	last->prev = NULL;
	last->next = *head;
	(*head)->prev = last;
	*head = last;
}

void	rra(t_ps *ps)
{
	reverse_rotate(&ps->a);
	write(1, "rra\n", 4);
}

void	rrb(t_ps *ps)
{
	reverse_rotate(&ps->b);
	write(1, "rrb\n", 4);
}

void	rrr(t_ps *ps)
{
	reverse_rotate(&ps->a);
	reverse_rotate(&ps->b);
	write(1, "rrr\n", 4);
}
