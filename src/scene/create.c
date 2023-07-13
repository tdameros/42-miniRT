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
#include "light.h"
#include "ray_tracer/texture.h"

void    scene_pilier(t_scene *scene);

int	init_scene(t_scene *scene)
{
    scene_pilier(scene);
    return (0);
	t_objects		objects;
	t_object		object;
	t_lights		lights;
    t_light         light;
	t_material		material;

	initialize_objects_array(&objects, 10);
	initialize_lights_array(&lights, 10);

    material = material_create(vector3f_create(1, 0, 0), 0, 0);
//	material.is_checked_pattern = true;
    material.checked_pattern_albedo = vector3f_create(0, 0, 0);
    material.checked_pattern_size = vector2f_create(20, 10);
    material.checked_pattern_albedo = vector3f_create(1, 1, 1);
//	object = sphere_create(vector3f_create(0, 0, 0), 1, material);
//	object = plane_create(vector3f_create(0, 0, 0), vector3f_create(0, 1, 0), material);
    t_object_size size = {1, 2.f};
    object = cone_create(vector3f_create(1, 1, 1), vector3f_create(0, 1, 0), size, material);
//	object = cylinder_create(vector3f_create(1, 1, 1), vector3f_create(0, 1, 0), 1, 2.0f, material);
    add_object_in_objects(&objects, object);
    // Plane
    material = material_create(vector3f_create(1.0f, 1.0f, 1.0f), 0.1f, 0);
//	material.is_damier = true;
    object = plane_create(vector3f_create(0.0f, -1.f, 0),
                          vector3f_create(0, 1, 0), material);
    add_object_in_objects(&objects, object);
//	material = material_create(vector3f_create(1.0f, 1.0f, 0.2f), 0.1f, 0);
//
//	object = plane_create(vector3f_create(0.0f, 0.0f, 10.0f),
//						  vector3f_create(0, 0, -1), material);
//	add_object_in_objects(&objects, object);
//
//	material = material_create(vector3f_create(1.0f, 0.0f, 0.2f), 0.1f, 0);
//	object = plane_create(vector3f_create(0.0f, 0.0f, -10.0f),
//						  vector3f_create(0, 0, 1), material);
//	add_object_in_objects(&objects, object);
//
//	material = material_create(vector3f_create(0.7f, 0.3f, 0.2f), 0.1f, 0);
//	object = plane_create(vector3f_create(10.0f, 0.0f, 0.0f),
//						  vector3f_create(-1, 0, 0), material);
//	add_object_in_objects(&objects, object);
//
//	material = material_create(vector3f_create(0.7f, 0.3f, 0.9f), 0.1f, 0);
//	object = plane_create(vector3f_create(-10.0f, 0.0f, 0.0f),
//						  vector3f_create(1, 0, 0), material);
//	add_object_in_objects(&objects, object);
//
//	material = material_create(vector3f_create(0.3f, 0.3f, 0.3f), 0.1f, 0);
//	object = plane_create(vector3f_create(0.0f, 10.0f, 0.0f),
//						  vector3f_create(0, -1, 0), material);
//	add_object_in_objects(&objects, object);

    light = light_create(vector3f_create(5, 5, 5), vector3f_create(1, 0, 0), 0.5f);
    add_light_in_lights(&lights, light);

    light = light_create(vector3f_create(-5, 5, 5), vector3f_create(0, 1, 0), 0.5f);
    add_light_in_lights(&lights, light);

    light = light_create(vector3f_create(5, 5, -5), vector3f_create(0, 0, 1), 0.5f);
    add_light_in_lights(&lights, light);

    scene->sky_color = vector3f_create(0, 0, 0);
    scene->ambient_light.color = vector3f_create(1, 1, 1);
    scene->ambient_light.brightness = 0.2f;
    scene->objects = objects;
    scene->lights = lights;
    return (0);
}

void    scene_pilier(t_scene *scene)
{
    t_objects   objects;
    t_object	object;
    t_lights	lights;
    t_light     light;
    t_material  material;

    initialize_objects_array(&objects, 10);
    initialize_lights_array(&lights, 10);

    material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
//	material.is_checked_pattern = true;
	material.checked_pattern_size = vector2f_create(10.f, 10.f);
	material.checked_pattern_albedo = vector3f_create(0, 0, 0);
    object = plane_create(vector3f_create(0.f, -5.f, 0.f), vector3f_create(0, 1, 0), material);
    add_object_in_objects(&objects, object);

    material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
    object = plane_create(vector3f_create(0.f, 5.f, 0.f), vector3f_create(0.f, 1.f, 0.f), material);
    add_object_in_objects(&objects, object);

    material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
    object = plane_create(vector3f_create(0.f, 0.f, 25.f), vector3f_create(0.f, 0.f, 1.f), material);
    add_object_in_objects(&objects, object);

    material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
    object = plane_create(vector3f_create(0.f, 0.f, -25.f), vector3f_create(0.f, 0.f, 1.f), material);
    add_object_in_objects(&objects, object);

    material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
    object = plane_create(vector3f_create(-15.f, 0.f, 0.f), vector3f_create(1.f, 0.f, 0.f), material);
    add_object_in_objects(&objects, object);

    material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
    object = plane_create(vector3f_create(15.f, 0.f, 0.f), vector3f_create(1.f, 0.f, 0.f), material);
    add_object_in_objects(&objects, object);

    // sphere
    material = material_create(vector3f_create(1.f, 1.f, 1.0f), 0.f, 0.f);
    object = sphere_create(vector3f_create(0.f, -3.f, 15.f), 1.5f, material);
	load_texture_object(&object, "data/saturn.ppm");
	object.material.is_texture = true;
	object.material.is_checked_pattern = true;
    add_object_in_objects(&objects, object);

	material = material_create(vector3f_create(1.f, 1.f, 1.0f), 0.f, 0.f);
	object = sphere_create(vector3f_create(0.f, -3.f, 15.f), 1.5f, material);
	load_texture_object(&object, "data/earth.ppm");
	object.material.is_texture = true;
	object.material.is_checked_pattern = true;
	add_object_in_objects(&objects, object);

	material = material_create(vector3f_create(1.f, 1.f, 1.0f), 0.f, 0.f);
	object = sphere_create(vector3f_create(0.f, -3.f, 15.f), 1.5f, material);
	load_texture_object(&object, "data/moon.ppm");
	object.material.is_texture = true;
	object.material.is_checked_pattern = true;
	add_object_in_objects(&objects, object);

	material = material_create(vector3f_create(1.f, 1.f, 1.0f), 0.f, 0.f);
	object = sphere_create(vector3f_create(0.f, -3.f, 15.f), 1.5f, material);
	load_texture_object(&object, "data/2k_stars.ppm");
	object.material.is_texture = true;
	object.material.is_checked_pattern = true;
	add_object_in_objects(&objects, object);

//	exit(0);
    material = material_create(vector3f_create(0.0f, 0.0f, 0.0f), 0.f, 0.f);
    material.reflect = 0.9f;
    object = sphere_create(vector3f_create(10.f, -5.f, 10.f), 3.f, material);
    add_object_in_objects(&objects, object);

    material = material_create(vector3f_create(1.f, 0.5f, 0.0f), 0.f, 0.f);
    material.specular = 0.5f;
    t_object_size size = (t_object_size){3, 5};
    object = cone_create(vector3f_create(-10.f, 0.f, 10.f), vector3f_create(0.f, 1.f, 0.f), size, material);
    add_object_in_objects(&objects, object);
	light = light_create(vector3f_create(0, 1, 15), vector3f_create(1, 1, 1), 1.f);

	add_light_in_lights(&lights, light);
//    t_object_size size = (t_object_size) {0.25f, 2.f};
    scene->ambient_light = light_create(vector3f_create(0, 0, 0),
                                        vector3f_create(1, 1, 1), 0.2f);
    scene->sky_color = vector3f_create(0, 0, 0);
    scene->objects = objects;
    scene->lights = lights;
}