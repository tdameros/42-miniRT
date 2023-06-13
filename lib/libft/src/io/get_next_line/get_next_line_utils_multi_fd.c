/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_multi_fd.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:38:31 by vfries            #+#    #+#             */
/*   Updated: 2022/11/22 15:12:55 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_multi_fd.h"
#include <stdlib.h>

void	ft_bzero_stop_at_zero(void *s, size_t n)
{
	while (n-- > 0 && *(unsigned char *)s != 0)
		*(unsigned char *)s++ = 0;
}

void	lst_add_front(t_lst **head, char *data)
{
	t_lst	*new;

	if (data == NULL)
		return ;
	new = malloc(sizeof(t_lst));
	if (new == NULL)
		return ;
	new->data = data;
	new->next = *head;
	*head = new;
}

void	*lst_free(t_lst *lst)
{
	t_lst	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->data);
		free(lst);
		lst = next;
	}
	return (NULL);
}

void	lst_reverse(t_lst **lst)
{
	t_lst	*previous;
	t_lst	*current;
	t_lst	*next;

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
}
