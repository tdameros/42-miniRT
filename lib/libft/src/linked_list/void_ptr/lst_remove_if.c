/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_remove_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 02:10:05 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 02:10:06 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_linked_list.h"

static void	move_cursor(t_list **cursor, t_list **previous_node);

void	ft_list_remove_if(t_list **begin_list, int (*cmp)(void *),
		void (*free_fct)(void *))
{
	t_list	*previous_node;
	t_list	*cursor;

	previous_node = NULL;
	cursor = *begin_list;
	while (cursor != NULL)
	{
		if (cmp(cursor->content) == 0)
		{
			if (previous_node != NULL)
				previous_node->next = cursor->next;
			else
				*begin_list = cursor->next;
			if (free_fct)
				free_fct(cursor->content);
			free(cursor);
			if (previous_node != NULL)
				cursor = previous_node->next;
			else
				cursor = *begin_list;
		}
		else
			move_cursor(&cursor, &previous_node);
	}
}

static void	move_cursor(t_list **cursor, t_list **previous_node)
{
	*previous_node = *cursor;
	*cursor = (*cursor)->next;
}
