/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:38:12 by sklaokli          #+#    #+#             */
/*   Updated: 2026/09/06 00:35:12 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "action.h"
# include "sort.h"
# include "stack.h"
# include "utils.h"
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>

/**
 * @brief The content structure stored inside each stack node.
 *
 * @param value The actual integer value provided as argument.
 * @param index The relative rank (0 to N-1) used for efficient sorting.
 */
typedef struct s_nbr	t_nbr;

/**
 * @brief The main program state structure.
 *
 * @param a   Pointer to the head of Stack A (Double Linked List).
 * @param b   Pointer to the head of Stack B (Double Linked List).
 */
typedef struct s_ps		t_ps;

struct					s_nbr
{
	int					value;
	size_t				index;
};

struct					s_ps
{
	t_stack				*a;
	t_stack				*b;
};

/**
 * @brief Initializes the main structure and operation buffer.
 *
 * @param ps Pointer to the main program state.
 */
void					ps_init(t_ps *ps);

/**
 * @brief Clears both stacks and frees the operation buffer.
 *
 * @param ps Pointer to the main program state.
 */
void					ps_clear(t_ps *ps);

/**
 * @brief Parses input array and populates Stack A.
 *
 * @param head Address of the pointer to the head of the stack.
 * @param tab  Array of integers to parse.
 * @param size Size of the array.
 * @return true if successful, false on allocation failure.
 */
bool					parse_numbers(t_stack **head, int *tab, size_t size);

/**
 * @brief Allocates a new number structure.
 *
 * @param value The integer value for the new number.
 * @return Pointer to the new number struct, or NULL on failure.
 */
t_nbr					*number_new(int value);

/**
 * @brief Checks if the stack is already sorted.
 *
 * @param head Pointer to the first node of the stack.
 * @return true if sorted, false otherwise.
 */
bool					is_sorted(t_stack *head);

/**
 * @brief Assigns a rank (0..N-1) to every number in the stack.
 *
 * Allows algorithms to work with normalized indices 0-N instead of ints.
 *
 * @param head Pointer to the first node of the stack.
 * @param tab  Array of integers (used for ranking).
 * @param size Size of the array.
 */
void					set_indices(t_stack *head, int *tab, size_t size);

/**
 * @brief Binary search to find the rank of a value in a sorted array.
 *
 * @param tab   Sorted array of integers.
 * @param size  Size of the array.
 * @param value The value to search for.
 * @return The index (rank) of the value.
 */
size_t					get_rank(int *tab, size_t size, int value);

/**
 * @brief Helper to duplicate an integer array.
 *
 * @param src  Source array.
 * @param size Size of the array.
 * @return Pointer to the new duplicated array, or NULL on failure.
 */
int						*duplicate_tab(int *src, size_t size);

bool					push_swap(int *tab, size_t size);

#endif