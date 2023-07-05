/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlstclear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:51:32 by vfries            #+#    #+#             */
/*   Updated: 2023/03/03 17:43:23 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include <stdlib.h>

static void	free_all_next(t_dlist *next, void (*del)(void *));
static void	free_all_previous(t_dlist *next, void (*del)(void *));

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	if (lst == NULL || *lst == NULL)
		return ;
	free_all_next((*lst)->next, del);
	free_all_previous((*lst)->previous, del);
	if (del != NULL)
		del((*lst)->content);
	free(*lst);
	*lst = NULL;
}

static void	free_all_next(t_dlist *next, void (*del)(void *))
{
	t_dlist	*free_me;

	while (next != NULL)
	{
		free_me = next;
		next = next->next;
		if (del != NULL)
			del(free_me->content);
		free(free_me);
	}
}

static void	free_all_previous(t_dlist *next, void (*del)(void *))
{
	t_dlist	*free_me;

	while (next != NULL)
	{
		free_me = next;
		next = next->previous;
		if (del != NULL)
			del(free_me->content);
		free(free_me);
	}
}
