/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get_next_free_current.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 02:30:21 by vfries            #+#    #+#             */
/*   Updated: 2023/01/30 01:43:13 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stdlib.h>

t_list	*ft_lst_get_next_free_current(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	next = (*lst)->next;
	if (del != NULL)
		del((*lst)->content);
	free(*lst);
	*lst = next;
	return (next);
}
