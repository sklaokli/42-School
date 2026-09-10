/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 22:34:51 by sklaokli          #+#    #+#             */
/*   Updated: 2026/01/22 15:19:19 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

static void	push(t_stack **src, t_stack **dst)
{
	t_stack	*node;

	if (!src || !*src)
		return ;
	node = *src;
	*src = node->next;
	if (*src)
		(*src)->prev = NULL;
	node->next = *dst;
	if (*dst)
		(*dst)->prev = node;
	*dst = node;
}

void	pa(t_ps *ps)
{
	push(&ps->b, &ps->a);
	write(1, "pa\n", 3);
}

void	pb(t_ps *ps)
{
	push(&ps->a, &ps->b);
	write(1, "pb\n", 3);
}
