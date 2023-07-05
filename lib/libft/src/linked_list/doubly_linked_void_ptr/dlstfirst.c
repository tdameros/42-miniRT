/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlstfirst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:26:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/24 01:26:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"

t_dlist	*ft_dlstfirst(const t_dlist *list)
{
	if (list == NULL)
		return (NULL);
	while (list->previous != NULL)
		list = list->previous;
	return ((t_dlist *)list);
}
