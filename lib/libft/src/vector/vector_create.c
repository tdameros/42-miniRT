/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:56:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/14 18:56:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_create(t_vector *vector, const size_t elem_size,
		const size_t size)
{
	if (size == 0)
	{
		ft_bzero(vector, sizeof(*vector));
		vector->elem_size = elem_size;
		return (VECTOR_SUCCESS);
	}
	vector->data = malloc(size * elem_size);
	if (vector->data == NULL)
	{
		ft_bzero(vector, sizeof(*vector));
		vector->elem_size = elem_size;
		return (VECTOR_ALLOCATION_FAILED);
	}
	vector->size = size;
	vector->elem_size = elem_size;
	vector->length = 0;
	return (VECTOR_SUCCESS);
}
