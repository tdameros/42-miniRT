/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_of_lst_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 06:10:19 by vfries            #+#    #+#             */
/*   Updated: 2023/01/27 06:15:50 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stdlib.h>

void	ft_lst_of_lst_clear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		node = (*lst)->content;
		ft_lstclear(&node, del);
		free(*lst);
		*lst = next;
	}
}
