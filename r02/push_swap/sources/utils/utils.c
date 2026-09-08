/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 00:05:35 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/08 12:35:20 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// bool	is_valid_zero(char *str)
// {
// 	while ((*str >= 9 && *str <= 13) || (*str == 32))
// 		str++;
// 	if (*str == '-' || *str == '+')
// 		str++;
// 	while (*str)
// 	{
// 		if ((*str == '0'))
// 			str++;
// 		else
// 			return (false);
// 	}
// 	return (true);
// }

long	ft_atol(char *str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if ((*str >= '0' && *str <= '9'))
			res = (res * 10) + (*str - '0');
		else
			return (0);
		str++;
	}
	return (sign * res);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dst;

	i = 0;
	while (src[i])
		i++;
	dst = malloc(i + 1);
	if (!dst)
		return (NULL);
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

void	free_matrix_2d(void **matrix)
{
	int	index;

	index = 0;
	if (!matrix)
		return ;
	while (matrix[index])
		free(matrix[index++]);
	free(matrix);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
