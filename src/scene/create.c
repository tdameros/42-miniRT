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
	t_material		material;

	initialize_objects_array(&objects, 10);

	material = material_create(vector3f_create(1, 0, 1), 0, 0);
//	material.emissive_color = vector3f_create(1, 1, 1);
//	material.emissive_power = 2.0f;
	object = sphere_create(vector3f_create(0, 0, 0), 1, material);
	add_object_in_objects(&objects, object);

	material = material_create(vector3f_create(0.8f, 0.5f, 0.2f), 0.1f, 0);
	material.emissive_color = vector3f_create(1, 1, 1);
	material.emissive_color = (t_vector3f){1.f, 1.f, 1.f};
	material.emissive_power = 100.0f;
	object = sphere_create(vector3f_create(32.0f, 3.8f, -32.0f), 11, material);
	add_object_in_objects(&objects, object);

	material = material_create(vector3f_create(0.2f, 0.3f, 1.0f), 0.1f, 0);
	object = sphere_create(vector3f_create(2, -101, 0), 100, material);
	add_object_in_objects(&objects, object);

	scene->sky_color = vector3f_create(0.0f, 0.0f, 0.0f);
	scene->sky_color = vector3f_create(0.1f, 0.1f, 0.1f);
	scene->light.position = vector3f_create(5, 5, 5);
	scene->light.color = vector3f_create(1, 1, 1);
	scene->light.brightness = 1;
	scene->ambient_light.color = vector3f_create(1, 1, 1);
	scene->ambient_light.brightness = 0;
	scene->objects = objects;
	return (0);
}
