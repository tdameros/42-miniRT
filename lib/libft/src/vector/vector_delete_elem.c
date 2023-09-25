/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_delete_elem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:43:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/14 19:43:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

static void	remove_elem_from_sorted_vector(t_vector *vector,
				void *elem_to_remove);
static void	remove_elem_from_unsorted_vector(t_vector *vector,
				void *elem_to_remove);

void	ft_vector_delete_elem(t_vector *vector, const size_t index,
			const bool keep_same_order)
{
	void	*elem_to_remove;

	if (index >= vector->length)
		return ;
	elem_to_remove = ft_vector_get_ptr_to_elem(vector, index);
	if (keep_same_order)
		remove_elem_from_sorted_vector(vector, elem_to_remove);
	else
		remove_elem_from_unsorted_vector(vector, elem_to_remove);
	vector->length--;
}

static void	remove_elem_from_sorted_vector(t_vector *vector,
				void *elem_to_remove)
{
	const size_t	size_to_move
		= (vector->data + vector->length * vector->elem_size)
		- elem_to_remove - vector->elem_size;

	ft_memmove(elem_to_remove, elem_to_remove + vector->elem_size,
		size_to_move);
}

static void	remove_elem_from_unsorted_vector(t_vector *vector,
				void *elem_to_remove)
{
	const void	*last_elem = vector->data
		+ (vector->length - 1) * vector->elem_size;

	ft_memmove(elem_to_remove, last_elem, vector->elem_size);
}
