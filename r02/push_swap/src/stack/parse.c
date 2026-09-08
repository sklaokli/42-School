/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:00:00 by sklaokli          #+#    #+#             */
/*   Updated: 2026/01/22 16:00:00 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_nbr	*number_new(int value)
{
	t_nbr	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = value;
	new->index = 0;
	return (new);
}

bool	parse_numbers(t_stack **head, int *tab, size_t size)
{
	size_t	i;
	t_nbr	*nbr;
	t_stack	*new;

	i = 0;
	while (i < size)
	{
		nbr = number_new(tab[i]);
		if (!nbr)
		{
			stack_clear(head, free);
			return (false);
		}
		new = stack_new(nbr);
		if (!new)
		{
			free(nbr);
			stack_clear(head, free);
			return (false);
		}
		stack_add(head, new);
		i++;
	}
	return (true);
}
