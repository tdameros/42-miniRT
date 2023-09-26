/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_change_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:00:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 19:53:16 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_change_size(t_vector *vector, const size_t size)
{
	void	*new_data;

	if (size == vector->size)
		return (VECTOR_SUCCESS);
	if (size < vector->length)
		return (VECTOR_SIZE_TOO_SMALL);
	new_data = malloc(size * vector->elem_size);
	if (new_data == NULL)
		return (VECTOR_ALLOCATION_FAILED);
	ft_memmove(new_data, vector->data, vector->length * vector->elem_size);
	vector->size = size;
	free(vector->data);
	vector->data = new_data;
	return (VECTOR_SUCCESS);
}
