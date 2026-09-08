/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:36:11 by sklaokli          #+#    #+#             */
/*   Updated: 2026/04/17 22:46:48 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	int		*tab;
	size_t	size;

	if (argc < 2)
		return (EXIT_FAILURE);
	tab = args_to_tab(argc, argv, &size);
	if (!tab)
	{
		write(2, "Error\n", 6);
		return (EXIT_FAILURE);
	}
	if (!push_swap(tab, size))
	{
		write(2, "Error\n", 6);
		free(tab);
		return (EXIT_FAILURE);
	}
	free(tab);
	return (EXIT_SUCCESS);
}
