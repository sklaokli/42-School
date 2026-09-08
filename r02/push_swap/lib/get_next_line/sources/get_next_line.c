/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:11:24 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/12 15:33:48 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_leftover(char *buffer)
{
	int		len;
	char	*tmp;

	if (!buffer)
		return (NULL);
	len = 0;
	while (buffer[len])
	{
		if (buffer[len] == '\n' || !buffer[len])
			break ;
		len++;
	}
	tmp = gnl_substr(buffer, len + 1, gnl_strlen(buffer));
	return (free(buffer), tmp);
}

char	*get_one_line(char *buffer)
{
	int		len;
	char	*tmp;

	if (!buffer)
		return (NULL);
	len = 0;
	while (buffer[len])
	{
		if (buffer[len] == '\n' || !buffer[len])
			break ;
		len++;
	}
	tmp = gnl_substr(buffer, 0, len + 1);
	return (tmp);
}

char	*gnl_free(char *buffer, char *tmp)
{
	char	*res;

	res = gnl_strjoin(buffer, tmp);
	return (free(buffer), res);
}

char	*get_buffer(int fd, char *buffer)
{
	int		byte;
	char	*tmp;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (!gnl_newline_found(buffer))
	{
		byte = read(fd, tmp, BUFFER_SIZE);
		if (byte == -1)
			return (free(buffer), free(tmp), NULL);
		else if (byte == 0)
			return (free(tmp), buffer);
		tmp[byte] = '\0';
		buffer = gnl_free(buffer, tmp);
	}
	return (free(tmp), buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[1024];

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = get_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_one_line(buffer[fd]);
	buffer[fd] = get_leftover(buffer[fd]);
	return (line);
}
