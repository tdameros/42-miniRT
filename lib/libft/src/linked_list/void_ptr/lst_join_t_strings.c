/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_join_t_strings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 02:51:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/12 02:51:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_string.h"
#include "ft_linked_list.h"
#include "ft_mem.h"

static size_t	get_len(t_list *list, t_string separator);
static void		fill_data(t_string *dest, t_list *list, t_string separator);

t_string	lst_join_t_strings(t_list *list, const t_string separator)
{
	t_string	result;

	if (list == NULL)
		return ((t_string){.data = NULL, .len = 0});
	ft_bzero(&result, sizeof(result));
	result.len = get_len(list, separator);
	result.data = malloc(result.len);
	if (result.data == NULL)
		return ((t_string){.data = NULL, .len = 0});
	fill_data(&result, list, separator);
	return (result);
}

static size_t	get_len(t_list *list, const t_string separator)
{
	size_t		result;
	t_string	*current_string;

	result = 0;
	while (true)
	{
		current_string = list->content;
		result += current_string->len;
		list = list->next;
		if (list == NULL)
			return (result);
		result += separator.len;
	}
}

static void	fill_data(t_string *dest, t_list *list, const t_string separator)
{
	t_string	*current_string;
	size_t		i;
	size_t		j;

	i = 0;
	while (true)
	{
		current_string = list->content;
		j = 0;
		while (j < current_string->len)
			dest->data[i++] = current_string->data[j++];
		list = list->next;
		if (list == NULL)
			return ;
		j = 0;
		while (j < separator.len)
			dest->data[i++] = separator.data[j++];
	}
}
