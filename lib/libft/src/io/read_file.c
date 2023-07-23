/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 07:48:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/11 07:48:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "ft_linked_list.h"
#include "ft_string.h"
#include "ft_mem.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static t_list	*read_file_content(int fd);
static int		add_string_to_list(t_list **list, const char *buf, ssize_t len);

t_string	ft_read_file(const char *file_name)
{
	int			fd;
	t_list		*lines;
	t_string	result;

	errno = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return ((t_string){.data = NULL, .len = 0});
	lines = read_file_content(fd);
	close(fd);
	if (lines == NULL)
		return ((t_string){.data = NULL, .len = 0});
	result = lst_join_t_strings(lines, (t_string){.data = NULL, .len = 0});
	ft_lstclear(&lines, &t_string_free);
	return (result);
}

static t_list	*read_file_content(int fd)
{
	char		buf[BUFFER_SIZE];
	t_list		*list;
	ssize_t		tmp;

	list = NULL;
	tmp = read(fd, buf, BUFFER_SIZE);
	while (tmp > 0)
	{
		if (add_string_to_list(&list, buf, tmp) < 0)
		{
			ft_lstclear(&list, &t_string_free);
			return (NULL);
		}
		tmp = read(fd, buf, BUFFER_SIZE);
	}
	return (ft_lst_reverse(&list));
}

static int	add_string_to_list(t_list **list, const char *buf, ssize_t len)
{
	t_string	*string;
	char		*string_data;
	t_list		*node;

	string_data = malloc(len);
	string = malloc(sizeof(*string));
	node = ft_lstnew(string);
	if (string_data == NULL || string == NULL || node == NULL)
	{
		free(string_data);
		free(string);
		free(node);
		return (-1);
	}
	string->data = string_data;
	string->len = len;
	while (len--)
		string_data[len] = buf[len];
	ft_lstadd_front(list, node);
	return (0);
}
