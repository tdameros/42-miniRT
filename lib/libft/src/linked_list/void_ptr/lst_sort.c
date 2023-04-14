/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 02:09:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 02:09:52 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"

static t_list	*partition(t_list *first, t_list *last,
					int (*f)(void *, void *));
static void		quick_sort(t_list *first, t_list *last,
					int (*f)(void *, void *));

void	ft_lst_sort(t_list *lst, int (*f)(void *, void *))
{
	t_list	*last;

	last = lst;
	if (last == NULL)
		return ;
	while (last->next != NULL)
		last = last->next;
	quick_sort(lst, last, f);
}

static void	quick_sort(t_list *first, t_list *last, int (*f)(void *, void *))
{
	t_list	*pivot;

	if (first == last)
		return ;
	pivot = partition(first, last, f);
	if (pivot != NULL && pivot->next != NULL)
		quick_sort(pivot->next, last, f);
	if (pivot != NULL && first != pivot)
		quick_sort(first, pivot, f);
}

static t_list	*partition(t_list *first, t_list *last,
					int (*f)(void *, void *))
{
	t_list	*pivot;
	t_list	*front;
	void	*temp;

	pivot = first;
	front = first;
	while (front != NULL && front != last)
	{
		if (f(front->content, last->content) < 0)
		{
			pivot = first;
			temp = first->content;
			first->content = front->content;
			front->content = temp;
			first = first->next;
		}
		front = front->next;
	}
	temp = first->content;
	first->content = last->content;
	last->content = temp;
	return (pivot);
}
