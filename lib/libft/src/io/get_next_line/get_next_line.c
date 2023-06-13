/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:54:10 by vfries            #+#    #+#             */
/*   Updated: 2022/11/17 01:52:25 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif

void	update_buffer(char *buffer)
{
	size_t	end;
	size_t	start;

	end = 0;
	while (end < BUFFER_SIZE && buffer[end] && buffer[end] != '\n')
		end++;
	if (end == BUFFER_SIZE)
		return (ft_bzero_stop_at_zero(buffer, BUFFER_SIZE));
	if (buffer[end] == '\n')
		end++;
	start = 0;
	while (end < BUFFER_SIZE && buffer[end])
		buffer[start++] = buffer[end++];
	ft_bzero_stop_at_zero(buffer + start, end - start);
}

char	*dup_before_new_line(char *buffer, t_bool *new_line_found)
{
	ssize_t	len;
	char	*result;

	len = 0;
	while (len < BUFFER_SIZE - 1 && buffer[len] != '\n' && buffer[len])
		len++;
	if (buffer[len] == '\n')
		*new_line_found = TRUE;
	result = malloc(len + 2);
	if (result == NULL)
		return (NULL);
	result[len + 1] = '\0';
	while (len > -1)
	{
		result[len] = buffer[len];
		len--;
	}
	update_buffer(buffer);
	return (result);
}

size_t	get_line_len(t_lst *line_lst)
{
	size_t	len;
	char	*str_end;

	len = 0;
	while (line_lst)
	{
		str_end = line_lst->data;
		while (*str_end)
			str_end++;
		len += str_end - line_lst->data;
		line_lst = line_lst->next;
	}
	return (len);
}

char	*get_line(t_lst *line_lst)
{
	char	*line;
	char	*line_start;
	char	*list_str;
	t_lst	*current;

	lst_reverse(&line_lst);
	line = malloc(get_line_len(line_lst) + 1);
	if (line == NULL)
		return (lst_free(line_lst));
	line_start = line;
	current = line_lst;
	while (current)
	{
		list_str = current->data;
		while (*list_str)
			*line++ = *list_str++;
		current = current->next;
	}
	*line = '\0';
	lst_free(line_lst);
	return (line_start);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	t_lst		*line;
	t_bool		new_line_found;
	ssize_t		read_output;

	new_line_found = FALSE;
	if (BUFFER_SIZE < 1 || fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	if (buffer[0] == '\0')
		if (read(fd, buffer, BUFFER_SIZE) == -1)
			return (NULL);
	if (buffer[0] == '\0')
		return (NULL);
	line = NULL;
	lst_add_front(&line, dup_before_new_line(buffer, &new_line_found));
	while (new_line_found == FALSE)
	{
		read_output = read(fd, buffer, BUFFER_SIZE);
		if (read_output == -1)
			return (lst_free(line));
		if (read_output == 0)
			break ;
		lst_add_front(&line, dup_before_new_line(buffer, &new_line_found));
	}
	return (get_line(line));
}
