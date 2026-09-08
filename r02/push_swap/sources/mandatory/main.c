/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:48:28 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/08 12:04:12 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_data	stack;

	init_stack(&stack, argc, argv);
	if (!is_sorted(stack.a))
	{
		if (stack.size <= 5)
			tiny_sort(&stack);
		else if (stack.size > 5)
			butterfly_sort(&stack);
	}
	clear_program(&stack, NULL, EXIT_SUCCESS);
}

void	print_action(t_action action)
{
	if (action == SA)
		write(1, "sa\n", 3);
	else if (action == SB)
		write(1, "sb\n", 3);
	else if (action == PA)
		write(1, "pa\n", 3);
	else if (action == PB)
		write(1, "pb\n", 3);
	else if (action == RA)
		write(1, "ra\n", 3);
	else if (action == RB)
		write(1, "rb\n", 3);
	else if (action == RR)
		write(1, "rr\n", 3);
	else if (action == RRA)
		write(1, "rra\n", 4);
	else if (action == RRB)
		write(1, "rrb\n", 4);
	else if (action == RRR)
		write(1, "rrr\n", 4);
}
