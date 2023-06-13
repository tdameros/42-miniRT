/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:02:54 by vfries            #+#    #+#             */
/*   Updated: 2022/11/08 15:09:23 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include "stddef.h"

void	ft_lsti_iter(t_list_i *lst, void (*f)(int *))
{
	if (f == NULL)
		return ;
	while (lst)
	{
		f(&lst->content);
		lst = lst->next;
	}
}
