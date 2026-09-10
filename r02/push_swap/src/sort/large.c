/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 23:40:20 by sklaokli          #+#    #+#             */
/*   Updated: 2026/01/22 15:04:34 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/**
 * @brief Calculates the bit width of the largest index.
 *
 * Example: If size is 100, indices range from 0-99.
 * 99 in binary is 1100011, which needs 7 bits.
 *
 * @param size The total number of elements in the stack.
 * @return The number of bits needed to represent (size - 1).
 */
static int	get_max_bits(size_t size)
{
	int		bits;
	size_t	max_val;

	if (size == 0)
		return (0);
	max_val = size - 1;
	bits = 0;
	while ((max_val >> bits) != 0)
		bits++;
	return (bits);
}

static void	process_bit(t_ps *ps, int bit, size_t size)
{
	t_nbr	*nbr;
	size_t	j;

	j = 0;
	while (j < size)
	{
		nbr = (t_nbr *)ps->a->content;
		if (((nbr->index >> bit) & 1) == 1)
			ra(ps);
		else
			pb(ps);
		j++;
	}
}

void	sort_radix(t_ps *ps)
{
	int		i;
	size_t	size;
	int		max_bits;

	size = stack_size(ps->a);
	max_bits = get_max_bits(size);
	i = 0;
	while (i < max_bits)
	{
		process_bit(ps, i, size);
		while (ps->b)
			pa(ps);
		if (is_sorted(ps->a))
			return ;
		i++;
	}
}
