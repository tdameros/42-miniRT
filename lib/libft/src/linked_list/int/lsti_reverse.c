/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsti_reverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:22:03 by vfries            #+#    #+#             */
/*   Updated: 2023/01/06 05:38:56 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stddef.h>

t_list_i	*ft_lsti_reverse(t_list_i **lst)
{
	t_list_i	*previous;
	t_list_i	*current;
	t_list_i	*next;

	previous = NULL;
	current = *lst;
	while (current)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	*lst = previous;
	return (*lst);
}
