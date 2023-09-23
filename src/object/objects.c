/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:07:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/09 17:07:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "object.h"

int	initialize_objects_array(t_objects *objects, size_t size)
{
	if (size == 0)
		size = 1;
	objects->data = malloc(sizeof(*objects->data) * size);
	if (objects->data == NULL)
		return (-1);
	objects->size = size;
	objects->length = 0;
	return (0);
}

int	add_object_in_objects(t_objects *objects, t_object object)
{
	t_object	*temp;

	if (objects->size == 0)
		if (initialize_objects_array(objects, 10) < 0)
			return (-1);
	if (objects->length < objects->size)
		objects->data[objects->length] = object;
	else
	{
		temp = malloc(sizeof(*objects->data) * (objects->size * 2));
		if (temp == NULL)
			return (-1);
		ft_memcpy(temp, objects->data,
			sizeof(*objects->data) * objects->length);
		temp[objects->length] = object;
		free(objects->data);
		objects->data = temp;
		objects->size *= 2;
	}
	objects->length += 1;
	return (0);
}

int	remove_object_in_objects(t_objects *objects, size_t index)
{
	if (objects->length <= index)
		return (-1);
	free_object(&objects->data[index]);
	objects->data[index] = objects->data[objects->length - 1];
	objects->length -= 1;
	return (0);
}

void	free_object(t_object *object)
{
	material_free(&object->material);
	if (object->type == MESH)
	{
		mesh_free(&object->mesh);
		mesh_cache_free(&object->cache.mesh);
	}
	free(object->name);
	object->name = NULL;
}

void	free_objects(t_objects *objects)
{
	size_t	i;

	i = 0;
	while (i < objects->length)
	{
		free_object(&objects->data[i]);
		i++;
	}
	free(objects->data);
	objects->size = 0;
	objects->length = 0;
}

