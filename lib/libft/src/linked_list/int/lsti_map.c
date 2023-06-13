/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:06:15 by vfries            #+#    #+#             */
/*   Updated: 2022/11/08 15:14:37 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stddef.h>

t_list_i	*ft_lsti_map(t_list_i *lst, int (*f)(int))
{
	t_list_i	*new_list;
	t_list_i	*new_elem;

	if (f == NULL)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_elem = ft_lsti_new(f(lst->content));
		if (new_elem == NULL)
		{
			ft_lsti_clear(&new_list);
			return (NULL);
		}
		ft_lsti_add_front(&new_list, new_elem);
		lst = lst->next;
	}
	ft_lsti_reverse(&new_list);
	return (new_list);
}
