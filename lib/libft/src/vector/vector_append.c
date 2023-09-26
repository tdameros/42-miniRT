/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:20:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 19:53:09 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

static int	realloc_and_append(t_vector *dst, const t_vector *src,
				size_t needed_size);
static void	append(t_vector *dst, const t_vector *src);

int	ft_vector_append(t_vector *dst, const t_vector *src)
{
	const size_t	needed_size = dst->length + src->length;

	if (dst->elem_size != src->elem_size)
		return (VECTOR_VECTORS_ELEM_SIZE_DONT_MATCH);
	if (needed_size > dst->size)
		return (realloc_and_append(dst, src, needed_size));
	append(dst, src);
	return (VECTOR_SUCCESS);
}

static int	realloc_and_append(t_vector *dst, const t_vector *src,
				const size_t needed_size)
{
	void	*new_data;

	new_data = malloc(dst->elem_size * needed_size);
	if (new_data == NULL)
		return (VECTOR_ALLOCATION_FAILED);
	ft_memmove(new_data, dst->data, dst->elem_size * dst->length);
	free(dst->data);
	dst->data = new_data;
	append(dst, src);
	return (VECTOR_SUCCESS);
}

static void	append(t_vector *dst, const t_vector *src)
{
	ft_memmove(dst->data + dst->elem_size * dst->length, src->data,
		dst->elem_size * src->length);
	dst->length += src->length;
}
