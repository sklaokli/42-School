/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:11:48 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/12 14:20:02 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*get_buffer(int fd, char *buffer);
char	*gnl_free(char *buffer, char *tmp);
char	*get_one_line(char *buffer);
char	*get_leftover(char *buffer);

int		gnl_strlen(char *s);
int		gnl_newline_found(char *line);
char	*gnl_strdup(char *s);
char	*gnl_substr(char *s, int start, int len);
char	*gnl_strjoin(char *buffer, char *tmp);

#endif