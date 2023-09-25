/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:18:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/14 21:18:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "vectors.h"

int	vectors_int_initialize(t_vectors_int *vectors_int, size_t size)
{
	if (size == 0)
		size = 1;
	vectors_int->data = malloc(sizeof(*vectors_int->data) * size);
	if (vectors_int->data == NULL)
		return (-1);
	vectors_int->size = size;
	vectors_int->length = 0;
	return (0);
}

int	vectors_int_add(t_vectors_int *vectors_int, int n)
{
	int	*temp;

	if (vectors_int->length < vectors_int->size)
		vectors_int->data[vectors_int->length] = n;
	else
	{
		temp = malloc(sizeof(*vectors_int->data) * (vectors_int->size * 2));
		if (temp == NULL)
			return (-1);
		ft_memcpy(temp, vectors_int->data,
			sizeof(*vectors_int->data) * vectors_int->length);
		temp[vectors_int->length] = n;
		free(vectors_int->data);
		vectors_int->data = temp;
		vectors_int->size *= 2;
	}
	vectors_int->length += 1;
	return (0);
}

int	vectors_int_remove(t_vectors_int *vectors_int, const size_t index)
{
	if (vectors_int->length <= index)
		return (-1);
	vectors_int->data[index] = vectors_int->data[vectors_int->length - 1];
	vectors_int->length -= 1;
	return (0);
}

int	vectors_int_free(t_vectors_int *vectors_int)
{
	free(vectors_int->data);
	vectors_int->data = NULL;
	vectors_int->size = 0;
	vectors_int->length = 0;
	return (0);
}
