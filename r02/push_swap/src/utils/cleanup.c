/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 22:58:04 by sklaokli          #+#    #+#             */
/*   Updated: 2026/09/10 21:35:05 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void	skip_space(const char **str)
{
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
}

int	*duplicate_tab(int *src, size_t size)
{
	int		*dst;
	size_t	i;

	dst = malloc(sizeof(*dst) * size);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

void	swap_ints(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

bool	has_duplicates(const int *tab, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] == tab[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}
