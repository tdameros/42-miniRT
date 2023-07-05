/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlstsize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:39:15 by vfries            #+#    #+#             */
/*   Updated: 2023/03/03 17:51:20 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"

size_t	ft_dlstsize(t_dlist *lst)
{
	size_t	size;
	t_dlist	*cursor;

	if (lst == NULL)
		return (0);
	size = 1;
	cursor = lst->next;
	while (cursor != NULL)
	{
		size++;
		cursor = cursor->next;
	}
	cursor = lst->previous;
	while (cursor != NULL)
	{
		size++;
		cursor = cursor->previous;
	}
	return (size);
}
