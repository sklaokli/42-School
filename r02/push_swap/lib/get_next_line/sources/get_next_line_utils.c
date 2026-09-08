/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:11:38 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/12 14:18:53 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	gnl_newline_found(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*gnl_strdup(char *s)
{
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	res = (char *)malloc(gnl_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (s[++i])
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}

char	*gnl_substr(char *s, int start, int len)
{
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	if (start >= gnl_strlen(s))
		return (NULL);
	if (len > gnl_strlen(s) - start)
		len = gnl_strlen(s) - start;
	s += start;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len)
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}

char	*gnl_strjoin(char *buffer, char *tmp)
{
	int		i;
	char	*res;

	if (!buffer && !tmp)
		return (NULL);
	if (!buffer || !tmp)
		return (gnl_strdup(tmp));
	res = (char *)malloc(gnl_strlen(buffer) + gnl_strlen(tmp) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (*buffer)
		res[i++] = *buffer++;
	while (*tmp)
		res[i++] = *tmp++;
	res[i] = '\0';
	return (res);
}
