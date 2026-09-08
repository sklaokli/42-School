/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:43:40 by sklaokli          #+#    #+#             */
/*   Updated: 2026/04/17 22:50:52 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

size_t	stack_size(t_stack *head)
{
	size_t	size;

	if (!head)
		return (0);
	size = 0;
	while (head)
	{
		size++;
		head = head->next;
	}
	return (size);
}

t_stack	*stack_last(t_stack *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	stack_clear(t_stack **head, void (*del)(void *))
{
	t_stack	*cur;
	t_stack	*next;

	if (!head || !*head || !del)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		del(cur->content);
		free(cur);
		cur = next;
	}
	*head = NULL;
}
