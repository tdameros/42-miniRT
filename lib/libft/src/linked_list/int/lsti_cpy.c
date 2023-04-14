/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsti_cpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 03:46:42 by vfries            #+#    #+#             */
/*   Updated: 2023/01/02 03:53:56 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"

t_list_i	*ft_lsti_cpy(t_list_i *lst)
{
	t_list_i	*new;
	t_list_i	*new_node;

	new = NULL;
	while (lst != NULL)
	{
		new_node = ft_lsti_new(lst->content);
		if (new_node == NULL)
		{
			ft_lsti_clear(&new);
			return (NULL);
		}
		ft_lsti_add_front(&new, new_node);
		lst = lst->next;
	}
	ft_lsti_reverse(&new);
	return (new);
}
