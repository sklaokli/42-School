/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:45:54 by sklaokli          #+#    #+#             */
/*   Updated: 2026/09/06 00:35:12 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"

t_stack	*stack_new(void *content)
{
	t_stack	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->content = content;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	stack_add(t_stack **head, t_stack *new)
{
	t_stack	*last;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		new->prev = NULL;
	}
	else if (*head)
	{
		last = stack_last(*head);
		last->next = new;
		new->prev = last;
	}
}

void	ps_init(t_ps *ps)
{
	ps->a = NULL;
	ps->b = NULL;
}

void	ps_clear(t_ps *ps)
{
	if (!ps)
		return ;
	stack_clear(&ps->a, free);
	stack_clear(&ps->b, free);
	ps->a = NULL;
	ps->b = NULL;
}
