/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 23:00:00 by sklaokli          #+#    #+#             */
/*   Updated: 2026/09/06 00:35:12 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_H
# define ACTION_H

# include "push_swap.h"
# include "stack.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_ps	t_ps;

/** @brief Swap A: Swaps the first two elements of stack A. */
void				sa(t_ps *ps);

/** @brief Swap B: Swaps the first two elements of stack B. */
void				sb(t_ps *ps);

/** @brief Swap S: Performs sa and sb simultaneously. */
void				ss(t_ps *ps);

/** @brief Push A: Moves the top element of stack B to the top of stack A. */
void				pa(t_ps *ps);

/** @brief Push B: Moves the top element of stack A to the top of stack B. */
void				pb(t_ps *ps);

/** @brief Rotate A: Shifts stack A up (first becomes last). */
void				ra(t_ps *ps);

/** @brief Rotate B: Shifts stack B up (first becomes last). */
void				rb(t_ps *ps);

/** @brief Rotate R: Performs ra and rb simultaneously. */
void				rr(t_ps *ps);

/** @brief Reverse Rotate A: Shifts stack A down (last becomes first). */
void				rra(t_ps *ps);

/** @brief Reverse Rotate B: Shifts stack B down (last becomes first). */
void				rrb(t_ps *ps);

/** @brief Reverse Rotate R: Performs rra and rrb simultaneously. */
void				rrr(t_ps *ps);

#endif