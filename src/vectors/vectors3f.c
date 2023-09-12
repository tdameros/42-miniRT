/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/08/08 11:47:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "vectors.h"

int	vectors3f_initialize(t_vectors3f *vectors3f, size_t size)
{
	if (size == 0)
		size = 1;
	vectors3f->data = malloc(sizeof(*vectors3f->data) * size);
	if (vectors3f->data == NULL)
		return (-1);
	vectors3f->size = size;
	vectors3f->length = 0;
	return (0);
}

int	vectors3f_add(t_vectors3f *vectors3f, t_vector3f vector3f)
{
	t_vector3f	*temp;

	if (vectors3f->length < vectors3f->size)
		vectors3f->data[vectors3f->length] = vector3f;
	else
	{
		temp = malloc(sizeof(*vectors3f->data) * (vectors3f->size * 2));
		if (temp == NULL)
			return (-1);
		ft_memcpy(temp, vectors3f->data,
			sizeof(*vectors3f->data) * vectors3f->length);
		temp[vectors3f->length] = vector3f;
		free(vectors3f->data);
		vectors3f->data = temp;
		vectors3f->size *= 2;
	}
	vectors3f->length += 1;
	return (0);
}

int	vectors3f_remove(t_vectors3f *vectors3f, const size_t index)
{
	if (vectors3f->length <= index)
		return (-1);
	vectors3f->data[index] = vectors3f->data[vectors3f->length - 1];
	vectors3f->length -= 1;
	return (0);
}

int	vectors3f_free(t_vectors3f *vectors3f)
{
	free(vectors3f->data);
	vectors3f->size = 0;
	vectors3f->length = 0;
	return (0);
}

int	vectors3f_deep_copy(t_vectors3f *dst, const t_vectors3f *src)
{
	vectors3f_free(dst);
	dst->data = malloc(sizeof(*dst->data) * src->length);
	if (dst->data == NULL)
		return (-1);
	dst->size = src->length;
	dst->length = src->length;
	ft_memcpy(dst->data, src->data, sizeof(*dst->data) * src->length);
	return (0);
}
