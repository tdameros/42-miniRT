/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_reverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:22:03 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 02:10:22 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"

static void	swap_next_and_previous(t_dlist *node);

t_dlist	*ft_dlst_reverse(t_dlist **lst)
{
	t_dlist	*cursor;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	cursor = *lst;
	while (cursor->next)
	{
		swap_next_and_previous(cursor);
		cursor = cursor->previous;
	}
	swap_next_and_previous(cursor);
	*lst = cursor;
	return (*lst);
}

static void	swap_next_and_previous(t_dlist *node)
{
	t_dlist	*tmp;

	tmp = node->next;
	node->next = node->previous;
	node->previous = tmp;
}
