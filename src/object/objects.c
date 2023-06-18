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
#include <stdio.h>

#include "object.h"
#include "libft.h"

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

	if (objects->length < objects->size)
		objects->data[objects->length] = object;
	else
	{
		temp = malloc(sizeof(*objects->data)
				* (objects->size * 2));
		if (temp == NULL)
			return (-1);
		ft_memcpy(temp, objects->data, sizeof(*objects->data) * objects->size);
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
	objects->data[index] = objects->data[objects->length - 1];
	objects->length -= 1;
	return (0);
}

int	free_objects(t_objects *objects)
{
	free(objects->data);
	objects->size = 0;
	objects->length = 0;
	return (0);
}

void	print_object2(t_object object)
{
	printf("Type: %d\n", object.type);
	printf("Position:");
	vector3f_print(object.position);
	printf("Normal:");
	vector3f_print(object.normal);
	printf("Albedo:");
	vector3f_print(object.material.albedo);
	printf("Radius: %f\n", object.radius);
}