/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:35:38 by sklaokli          #+#    #+#             */
/*   Updated: 2026/09/06 00:35:12 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	skip_space(const char **str)
{
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
}

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
	if (!ft_isdigit(**str))
		*error = true;
	while (ft_isdigit(**str))
	{
		num = num * 10 + (**str - '0');
		if ((sign == 1 && num > INT_MAX)
			|| (sign == -1 && num > -(long)INT_MIN))
			*error = true;
		(*str)++;
	}
	return ((int)(num * sign));
}

static size_t	count_nums(int argc, char **argv)
{
	size_t		count;
	int			i;
	const char	*ptr;

	count = 0;
	i = 1;
	while (i < argc)
	{
		ptr = argv[i];
		while (*ptr)
		{
			skip_space(&ptr);
			if (*ptr)
			{
				count++;
				if (*ptr == '+' || *ptr == '-')
					ptr++;
				while (ft_isdigit(*ptr))
					ptr++;
			}
		}
		i++;
	}
	return (count);
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

	*size = count_nums(argc, argv);
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
	return (tab);
}
