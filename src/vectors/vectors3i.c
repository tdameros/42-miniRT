/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:55:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/25 19:54:06 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "vectors.h"

int	vectors3i_initialize(t_vectors3i *vectors3i, size_t size)
{
	if (size == 0)
		size = 1;
	vectors3i->data = malloc(sizeof(*vectors3i->data) * size);
	if (vectors3i->data == NULL)
		return (-1);
	vectors3i->size = size;
	vectors3i->length = 0;
	return (0);
}

int	vectors3i_add(t_vectors3i *vectors3i, t_vector3i vector3i)
{
	t_vector3i	*temp;

	if (vectors3i->length < vectors3i->size)
		vectors3i->data[vectors3i->length] = vector3i;
	else
	{
		temp = malloc(sizeof(*vectors3i->data) * (vectors3i->size * 2));
		if (temp == NULL)
			return (-1);
		ft_memmove(temp, vectors3i->data,
			sizeof(*vectors3i->data) * vectors3i->length);
		temp[vectors3i->length] = vector3i;
		free(vectors3i->data);
		vectors3i->data = temp;
		vectors3i->size *= 2;
	}
	vectors3i->length += 1;
	return (0);
}

int	vectors3i_remove(t_vectors3i *vectors3i, const size_t index)
{
	if (vectors3i->length <= index)
		return (-1);
	vectors3i->data[index] = vectors3i->data[vectors3i->length - 1];
	vectors3i->length -= 1;
	return (0);
}

int	vectors3i_free(t_vectors3i *vectors3i)
{
	free(vectors3i->data);
	vectors3i->size = 0;
	vectors3i->length = 0;
	return (0);
}
