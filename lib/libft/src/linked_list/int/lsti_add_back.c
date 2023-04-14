/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:44:07 by vfries            #+#    #+#             */
/*   Updated: 2022/11/08 15:07:56 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stddef.h>

void	ft_lsti_add_back(t_list_i **lst, t_list_i *new)
{
	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else if (new != NULL)
		ft_lsti_last(*lst)->next = new;
}
