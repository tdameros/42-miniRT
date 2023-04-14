/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsti_get_next_free_current.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 02:30:21 by vfries            #+#    #+#             */
/*   Updated: 2023/01/23 16:28:41 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stdlib.h>

t_list_i	*ft_lsti_get_next_free_current(t_list_i **lst)
{
	t_list_i	*next;

	if (*lst == NULL)
		return (NULL);
	next = (*lst)->next;
	free(*lst);
	*lst = next;
	return (next);
}
