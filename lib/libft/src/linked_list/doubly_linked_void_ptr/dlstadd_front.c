/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlstadd_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:31:47 by vfries            #+#    #+#             */
/*   Updated: 2023/03/03 17:37:44 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stddef.h>

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	if (*lst != NULL)
		(*lst)->previous = new;
	*lst = new;
}
