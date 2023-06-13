/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 01:16:43 by vfries            #+#    #+#             */
/*   Updated: 2023/03/03 17:31:27 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"

void	ft_dlst_push(t_dlist **dst, t_dlist **src)
{
	t_dlist	*tmp;

	if (dst == NULL || src == NULL || *src == NULL)
		return ;
	tmp = *src;
	*src = (*src)->next;
	(*src)->previous = NULL;
	tmp->next = *dst;
	if (*dst != NULL)
		(*dst)->previous = tmp;
	*dst = tmp;
}
