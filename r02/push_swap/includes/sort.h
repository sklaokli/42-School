/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 23:39:55 by sklaokli          #+#    #+#             */
/*   Updated: 2026/01/22 15:50:46 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include "push_swap.h"
# include <stdlib.h>

typedef struct s_ps	t_ps;

/**
 * @brief Sorting strategy for exactly 2 numbers.
 *
 * Checks if the first two elements of stack A are in ascending order.
 * If not (first > second), performs a Swap A (sa) operation.
 *
 * @param ps Pointer to the main program state.
 */
void				sort_two(t_ps *ps);

/**
 * @brief Sorting strategy for exactly 3 numbers.
 *
 * Uses a hard-coded algorithm to sort 3 numbers in <= 2 moves.
 * Strategy:
 * 1. Identify the position of the largest number (index 2).
 * 2. Rotate or Reverse Rotate to move the largest number to the bottom.
 * 3. Check the remaining top two numbers and Swap (sa) if necessary.
 *
 * @param ps Pointer to the main program state.
 */
void				sort_three(t_ps *ps);

/**
 * @brief Main sorting strategy for large sets (Size > 3).
 *
 * Implements the Radix Sort algorithm using bitwise operations on indices.
 * 1. Iterates through bits from LSB to MSB.
 * 2. If a number's bit is 0, push to Stack B (pb).
 * 3. If a number's bit is 1, rotate Stack A (ra).
 * 4. Push all numbers back from B to A.
 * 5. Repeat until sorted.
 *
 * @param ps Pointer to the main program state.
 */
void				sort_radix(t_ps *ps);

#endif