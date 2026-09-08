/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 00:12:13 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 03:06:08 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	*last_node(void *list)
{
	t_list	*tmp;

	tmp = (t_list *)list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	node_addback(void **list, void *new)
{
	t_list	**tmp;

	tmp = (t_list **)list;
	if (!*tmp && new)
		*tmp = new;
	else if (*tmp && new)
		((t_list *)last_node(*tmp))->next = new;
}

int	list_size(void *list)
{
	int		size;
	t_list	*tmp;

	size = 0;
	tmp = (t_list *)list;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

t_stack	*new_stack(char *argv, long int value)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->argv = argv;
	new->value = value;
	new->next = NULL;
	return (new);
}
