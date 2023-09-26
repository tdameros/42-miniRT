/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:49:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 19:52:45 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

#define DEFAULT_SIZE 10

static int	add_elem_on_empty_vector(t_vector *vector, const void *new_elem);
static int	add_elem_on_full_vector(t_vector *vector, const void *new_elem);
static int	add_elem_on_non_full_vector(t_vector *vector, const void *new_elem);

int	ft_vector_add_elem(t_vector *vector, const void *new_elem)
{
	if (vector->data == NULL)
		return (add_elem_on_empty_vector(vector, new_elem));
	if (vector->length >= vector->size)
		return (add_elem_on_full_vector(vector, new_elem));
	return (add_elem_on_non_full_vector(vector, new_elem));
}

static int	add_elem_on_empty_vector(t_vector *vector, const void *new_elem)
{
	vector->data = malloc(DEFAULT_SIZE * vector->elem_size);
	if (vector->data == NULL)
		return (VECTOR_ALLOCATION_FAILED);
	vector->length = 1;
	vector->size = DEFAULT_SIZE;
	ft_memmove(vector->data, new_elem, vector->elem_size);
	return (VECTOR_SUCCESS);
}

static int	add_elem_on_full_vector(t_vector *vector, const void *new_elem)
{
	void			*new_data;
	const size_t	new_size = vector->size * 2;

	new_data = malloc(new_size * vector->elem_size);
	if (new_data == NULL)
		return (VECTOR_ALLOCATION_FAILED);
	ft_memmove(new_data, vector->data, vector->length * vector->elem_size);
	ft_memmove(new_data + (vector->length * vector->elem_size), new_elem,
		vector->elem_size);
	free(vector->data);
	vector->data = new_data;
	vector->size = new_size;
	vector->length++;
	return (VECTOR_SUCCESS);
}

static int	add_elem_on_non_full_vector(t_vector *vector, const void *new_elem)
{
	ft_memmove(vector->data + (vector->length * vector->elem_size), new_elem,
		vector->elem_size);
	vector->length++;
	return (VECTOR_SUCCESS);
}
