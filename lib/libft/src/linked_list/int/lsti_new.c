/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:44:30 by vfries            #+#    #+#             */
/*   Updated: 2022/10/13 22:25:52 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stdlib.h>

t_list_i	*ft_lsti_new(int content)
{
	t_list_i	*new;

	new = malloc(sizeof(t_list_i));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
