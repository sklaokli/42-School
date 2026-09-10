/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:35:38 by sklaokli          #+#    #+#             */
/*   Updated: 2026/09/10 21:35:05 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ps_atol_ptr(const char **str, bool *error)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	skip_space(str);
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	while (ft_isdigit(**str))
	{
		if (num <= (long)INT_MAX + 1)
			num = num * 10 + (**str - '0');
		if ((sign == 1 && num > INT_MAX)
			|| (sign == -1 && num > -(long)INT_MIN))
			*error = true;
		(*str)++;
	}
	return ((int)(num * sign));
}

static bool	is_valid_token(const char **str)
{
	skip_space(str);
	if (!**str)
		return (false);
	if (**str == '+' || **str == '-')
		(*str)++;
	if (!ft_isdigit(**str))
		return (false);
	while (ft_isdigit(**str))
		(*str)++;
	if (**str && **str != ' ' && !(**str >= 9 && **str <= 13))
		return (false);
	return (true);
}

static bool	count_and_validate(int argc, char **argv, size_t *count)
{
	int			i;
	const char	*ptr;
	size_t		arg_nums;

	*count = 0;
	i = 0;
	while (++i < argc)
	{
		ptr = argv[i];
		arg_nums = 0;
		while (*ptr)
		{
			skip_space(&ptr);
			if (!*ptr)
				break ;
			if (!is_valid_token(&ptr))
				return (false);
			arg_nums++;
		}
		if (arg_nums == 0)
			return (false);
		*count += arg_nums;
	}
	return (true);
}

static bool	fill_tab_from_arg(const char *str, int *tab, size_t *k)
{
	bool	error;

	error = false;
	while (*str)
	{
		skip_space(&str);
		if (*str)
		{
			tab[(*k)++] = ps_atol_ptr(&str, &error);
			if (error)
				return (false);
		}
	}
	return (true);
}

int	*args_to_tab(int argc, char **argv, size_t *size)
{
	int		*tab;
	int		i;
	size_t	k;

	if (!count_and_validate(argc, argv, size))
		return (NULL);
	tab = malloc(sizeof(int) * (*size));
	if (!tab)
		return (NULL);
	k = 0;
	i = 0;
	while (++i < argc)
	{
		if (!fill_tab_from_arg(argv[i], tab, &k))
		{
			free(tab);
			return (NULL);
		}
	}
	if (has_duplicates(tab, *size))
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}
