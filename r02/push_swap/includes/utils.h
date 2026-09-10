/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 23:07:42 by sklaokli          #+#    #+#             */
/*   Updated: 2026/09/10 21:35:05 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

bool	ft_isdigit(char c);
void	skip_space(const char **str);
void	swap_ints(int *a, int *b);
bool	has_duplicates(const int *tab, size_t size);
int		*args_to_tab(int argc, char **argv, size_t *size);

#endif