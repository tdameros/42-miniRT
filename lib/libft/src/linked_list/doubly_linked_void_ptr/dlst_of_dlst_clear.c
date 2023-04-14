/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_of_dlst_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 06:10:19 by vfries            #+#    #+#             */
/*   Updated: 2023/03/03 17:30:25 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stdlib.h>

void	ft_dlst_of_dlst_clear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*node;
	t_dlist	*next;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		node = (*lst)->content;
		ft_dlstclear(&node, del);
		free(*lst);
		*lst = next;
	}
}
