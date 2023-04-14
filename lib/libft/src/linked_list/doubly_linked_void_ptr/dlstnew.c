/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlstnew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:44:30 by vfries            #+#    #+#             */
/*   Updated: 2023/03/03 17:49:51 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stdlib.h>

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->previous = NULL;
	new->content = content;
	new->next = NULL;
	return (new);
}
