/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_get_next_free_current.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 02:30:21 by vfries            #+#    #+#             */
/*   Updated: 2023/03/03 17:29:10 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stdlib.h>

t_dlist	*ft_dlst_get_next_free_current(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*next;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	next = (*lst)->next;
	if (del != NULL)
		del((*lst)->content);
	free(*lst);
	next->previous = NULL;
	*lst = next;
	return (next);
}
