/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:20:37 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/08 12:14:38 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_stack(t_data *stack, int argc, char *argv[])
{
	int		i;
	int		j;
	char	**tmp;

	if (argc < 2)
		exit(EXIT_FAILURE);
	i = 0;
	stack->a = NULL;
	stack->b = NULL;
	while (argv[++i])
	{
		if (!*argv[i])
			clear_program(stack, "Error", EXIT_FAILURE);
		j = -1;
		tmp = ft_split(argv[i], ' ');
		while (tmp[++j])
			node_addback((void **)&stack->a, new_stack(\
				ft_strdup(tmp[j]), ft_atol(tmp[j])));
		free_matrix_2d((void **)tmp);
	}
	if (!stack->a || !parser(stack->a))
		clear_program(stack, "Error", EXIT_FAILURE);
	stack->size = list_size(stack->a);
	assign_sorted_index(stack->a);
}

bool	parser(t_stack *a)
{
	if (!a)
		return (false);
	while (a)
	{
		if (a->value < INT_MIN || a->value > INT_MAX)
			return (false);
		else if (has_duplicates(a))
			return (false);
		else if (a->value == 0)
		{
			if (a->argv[0] == '0' && a->argv[1] == '\0')
				return (true);
			if (a->argv[0] == '+' && a->argv[1] == '0' \
				&& a->argv[2] == '\0')
				return (true);
			else
				return (false);
		}
		a = a->next;
	}
	return (true);
}

bool	has_duplicates(t_stack *a)
{
	t_stack	*current;
	t_stack	*checker;

	current = a;
	while (current)
	{
		checker = current->next;
		while (checker)
		{
			if (current->value == checker->value)
				return (true);
			checker = checker->next;
		}
		current = current->next;
	}
	return (false);
}

void	assign_sorted_index(t_stack *a)
{
	int		index;
	t_stack	*current;
	t_stack	*compare;

	current = a;
	while (current)
	{
		index = 1;
		compare = a;
		while (compare)
		{
			if (compare->value < current->value)
				index++;
			compare = compare->next;
		}
		current->index = index;
		current = current->next;
	}
}

void	clear_program(t_data *stack, char *str, int exit_code)
{
	t_stack	*tmp;

	while (stack->a)
	{
		tmp = stack->a;
		stack->a = stack->a->next;
		free(tmp->argv);
		free(tmp);
	}
	if (str)
	{
		while (*str)
			write(2, str++, 1);
		write(2, "\n", 1);
	}
	exit(exit_code);
}
