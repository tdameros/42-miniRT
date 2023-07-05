/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_convert_to_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:11:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/14 22:11:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

static void	*make_copy_of_vector(const t_vector *vector);

void	*ft_vector_convert_to_array(t_vector *vector, size_t *size,
			const bool make_copy, const bool destroy_vector)
{
	void	*result;

	if (make_copy)
		result = make_copy_of_vector(vector);
	else
		result = vector->data;
	if (size != NULL)
		*size = vector->length;
	if (make_copy && destroy_vector)
		ft_vector_destroy(vector);
	else if (destroy_vector)
	{
		vector->data = NULL;
		ft_vector_destroy(vector);
	}
	return (result);
}

static void	*make_copy_of_vector(const t_vector *vector)
{
	void	*copy;

	copy = malloc(vector->length * vector->elem_size);
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, vector->data, vector->length * vector->elem_size);
	return (copy);
}
