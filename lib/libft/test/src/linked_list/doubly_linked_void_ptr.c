/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_void_ptr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 02:10:53 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 02:10:56 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

//
// Created by vfries on 3/4/23.
//

// SMALLEST needs to be smaller than BIGGEST
#define SMALLEST 0
#define BIGGEST 10

static t_dlist	*create_list(void);
static bool		check_list(t_dlist *lst, int start, int end, int increment);
static bool		check_push(t_dlist **lst);
static void		push_all(t_dlist **dst, t_dlist **src);

bool	ft_doubly_linked_void_ptr_test(void)
{
	t_dlist	*lst;

	lst = create_list();
	if (lst == NULL || check_list(lst, SMALLEST, BIGGEST, 1))
		return (ft_dlstclear(&lst, &free), true);
	if (check_list(ft_dlst_reverse(&lst), BIGGEST, SMALLEST, -1))
		return (ft_dlstclear(&lst, &free), true);
	ft_dlst_reverse(&lst);
	if (check_push(&lst))
		return (ft_dlstclear(&lst, &free), true);
	ft_dlstclear(&lst, &free);
	return (false);
}

static t_dlist	*create_list(void)
{
	t_dlist	*lst;
	int		i;
	int		*new_int;
	t_dlist	*new_node;

	lst = NULL;
	i = BIGGEST + 1;
	while (--i >= SMALLEST)
	{
		new_int = malloc(sizeof(int));
		new_node = ft_dlstnew(new_int);
		if (new_int == NULL || new_node == NULL)
		{
			ft_dlstclear(&lst, &free);
			free(new_int);
			free(new_node);
			return (NULL);
		}
		*new_int = i;
		ft_dlstadd_front(&lst, new_node);
	}
	return (lst);
}

static bool	check_list(t_dlist *lst, int start, int end, int increment)
{
	int	*content;
	int	i;

	i = start;
	while (lst->next)
	{
		content = lst->content;
		if (*content != i)
			return (true);
		i += increment;
		lst = lst->next;
	}
	if (i != end)
		return (true);
	while (lst)
	{
		content = lst->content;
		if (*content != i)
			return (true);
		i -= increment;
		lst = lst->previous;
	}
	if (i + 1 != start)
		return (true);
	return (false);
}

static bool	check_push(t_dlist **lst)
{
	t_dlist	*new_lst;
	int		i;

	new_lst = NULL;
	i = SMALLEST - 1;
	while (*lst)
	{
		ft_dlst_push(&new_lst, lst);
		if (check_list(*lst, i + 1, BIGGEST, 1)
			|| check_list(*lst, i, SMALLEST, 1))
			return (push_all(lst, &new_lst), true);
	}
	push_all(lst, &new_lst);
	return (false);
}

static void	push_all(t_dlist **dst, t_dlist **src)
{
	while (*src)
		ft_dlst_push(dst, src);
}
