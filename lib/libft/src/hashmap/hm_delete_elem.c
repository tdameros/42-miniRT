/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_delete_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:06:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/28 00:15:03 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"
#include "ft_string.h"
#include <stdlib.h>

static void	delete_hashmap_node(t_list *node, void (*del)(void*));

int	ft_hm_delete_elem(t_hashmap map, char *target, void (*del)(void *))
{
	t_list			*cursor;
	t_list			*temp_cursor;
	const size_t	index = ft_hm_get_index(target);

	cursor = map[index];
	if (cursor == NULL)
		return (-1);
	if (ft_strcmp(((t_hashmap_content *)cursor->content)->target, target) == 0)
	{
		map[index] = cursor->next;
		delete_hashmap_node(cursor, del);
		return (0);
	}
	while (cursor->next != NULL
		&& ft_strcmp(((t_hashmap_content *)cursor->next->content)->target,
			target) != 0)
		cursor = cursor->next;
	if (cursor->next == NULL)
		return (-1);
	temp_cursor = cursor->next;
	cursor->next = cursor->next->next;
	delete_hashmap_node(temp_cursor, del);
	return (0);
}

static void	delete_hashmap_node(t_list *node, void (*del)(void*))
{
	t_hashmap_content	*hm_content;

	hm_content = node->content;
	del(hm_content->content);
	free(hm_content->target);
	free(hm_content);
	free(node);
}
