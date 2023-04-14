/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlstmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:06:15 by vfries            #+#    #+#             */
/*   Updated: 2023/03/03 17:46:57 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stddef.h>

t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*new_list;
	t_dlist	*new_elem;

	if (f == NULL)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_elem = ft_dlstnew(f(lst->content));
		if (new_elem == NULL)
		{
			ft_dlstclear(&new_list, del);
			return (NULL);
		}
		ft_dlstadd_front(&new_list, new_elem);
		lst = lst->next;
	}
	ft_dlst_reverse(&new_list);
	return (new_list);
}
