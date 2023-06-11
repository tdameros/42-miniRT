/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/07 16:01:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "scene.h"
#include "object.h"

int	init_scene(t_scene *scene)
{
	t_objects		objects;
	t_object		object;

	initialize_objects_array(&objects, 10);
	object = sphere_create(vector3f_create(0, 0, 0), 0.5f,
						   vector3f_create(1, 0, 1));
	add_object_in_objects(&objects, object);
	object = sphere_create(vector3f_create(-4, 1, 0), 1.5f,
						   vector3f_create(0.2f, 0.3f, 1));
	add_object_in_objects(&objects, object);
	object = plane_create(vector3f_create(0, -0.5,0), vector3f_create(0, 1, 0),
						  vector3f_create(1, 1, 1));
	add_object_in_objects(&objects, object);
	scene->light.position = vector3f_create(5, 5, 5);
	scene->light.brightness = 1;
	scene->light.color = vector3f_create(0, 0, 0);
	scene->objects = objects;
	return (0);
}
