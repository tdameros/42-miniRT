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

#include "scene.h"
#include "object.h"
#include "light.h"
#include "engine.h"
#include "ray_tracer_gui_api.h"

void	scene_pilier(t_engine *engine);

int	init_scene(t_engine *engine)
{
	scene_pilier(engine);
	return (0);
	t_object		object;
	t_light         light;
	t_material		material;

	initialize_objects_array(&engine->scene.objects, 10);
	initialize_lights_array(&engine->scene.lights, 10);

	material = material_create(vector3f_create(1, 0, 0), 0, 0);
//	material.is_checked_pattern = true;
//    material.checked_pattern_albedo = vector3f_create(0, 0, 0);
//    material.checked_pattern_size = vector2f_create(20, 10);
//    material.checked_pattern_albedo = vector3f_create(1, 1, 1);
//	object = sphere_create(vector3f_create(0, 0, 0), 1, material);
//	object = plane_create(vector3f_create(0, 0, 0), vector3f_create(0, 1, 0), material);
	t_object_size size = {1, 2.f};
	object = cone_create(vector3f_create(1, 1, 1), vector3f_create(0, 1, 0), size, material);
//	object = cylinder_create(vector3f_create(1, 1, 1), vector3f_create(0, 1, 0), 1, 2.0f, material);
	add_object(engine, object);
	// Plane
	material = material_create(vector3f_create(1.0f, 1.0f, 1.0f), 0.1f, 0);
//	material.is_damier = true;
	object = plane_create(vector3f_create(0.0f, -1.f, 0),
						  vector3f_create(0, 1, 0), material);
	add_object(engine, object);
//	material = material_create(vector3f_create(1.0f, 1.0f, 0.2f), 0.1f, 0);
//
//	object = plane_create(vector3f_create(0.0f, 0.0f, 10.0f),
//						  vector3f_create(0, 0, -1), material);
//	add_object(engine, object);
//
//	material = material_create(vector3f_create(1.0f, 0.0f, 0.2f), 0.1f, 0);
//	object = plane_create(vector3f_create(0.0f, 0.0f, -10.0f),
//						  vector3f_create(0, 0, 1), material);
//	add_object(engine, object);
//
//	material = material_create(vector3f_create(0.7f, 0.3f, 0.2f), 0.1f, 0);
//	object = plane_create(vector3f_create(10.0f, 0.0f, 0.0f),
//						  vector3f_create(-1, 0, 0), material);
//	add_object(engine, object);
//
//	material = material_create(vector3f_create(0.7f, 0.3f, 0.9f), 0.1f, 0);
//	object = plane_create(vector3f_create(-10.0f, 0.0f, 0.0f),
//						  vector3f_create(1, 0, 0), material);
//	add_object(engine, object);
//
//	material = material_create(vector3f_create(0.3f, 0.3f, 0.3f), 0.1f, 0);
//	object = plane_create(vector3f_create(0.0f, 10.0f, 0.0f),
//						  vector3f_create(0, -1, 0), material);
//	add_object(engine, object);

	light = light_create(vector3f_create(5, 5, 5), vector3f_create(1, 0, 0), 0.5f);
	add_light(engine, light);

	light = light_create(vector3f_create(-5, 5, 5), vector3f_create(0, 1, 0), 0.5f);
	add_light(engine, light);

	light = light_create(vector3f_create(5, 5, -5), vector3f_create(0, 0, 1), 0.5f);
	add_light(engine, light);

	engine->scene.sky_color = vector3f_create(0, 0, 0);
	engine->scene.ambient_light.color = vector3f_create(1, 1, 1);
	engine->scene.ambient_light.brightness = 0.2f;
	return (0);
}

void	scene_pilier(t_engine *engine)
{
	t_object	object;
	t_light     light;
	t_material  material;

	initialize_objects_array(&engine->scene.objects, 10);
	initialize_lights_array(&engine->scene.lights, 10);

	material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
//	material.is_checked_pattern = true;
//	material.checked_pattern_size = vector2f_create(10.f, 10.f);
//	material.checked_pattern_albedo = vector3f_create(0, 0, 0);
	object = plane_create(vector3f_create(0.f, -5.f, 0.f), vector3f_create(0, 1, 0), material);
	add_object(engine, object);

	material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
	object = plane_create(vector3f_create(0.f, 5.f, 0.f), vector3f_create(0.f, 1.f, 0.f), material);
	add_object(engine, object);

	material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
	object = plane_create(vector3f_create(0.f, 0.f, 25.f), vector3f_create(0.f, 0.f, 1.f), material);
//	add_object(engine, object);

	material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
//	set_outline_normals_map(&material, "data/normals_map.ppm");
	object = plane_create(vector3f_create(0.f, 0.f, -25.f), vector3f_create(0.f, 0.f, 1.f), material);
	add_object(engine, object);

	material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
	object = plane_create(vector3f_create(-15.f, 0.f, 0.f), vector3f_create(1.f, 0.f, 0.f), material);
	add_object(engine, object);

	material = material_create(vector3f_create(0.4f, 0.4f, 0.4f), 0.f, 0.f);
	object = plane_create(vector3f_create(15.f, 0.f, 0.f), vector3f_create(1.f, 0.f, 0.f), material);
	add_object(engine, object);

	// sphere
	material = material_create(vector3f_create(1.f, 1.f, 1.0f), 0.f, 0.f);
	set_outline_texture(&material, "data/textures/saturn.ppm");
	object = sphere_create(vector3f_create(0.f, -3.f, 15.f), 1.5f, material);
//    add_object(engine, object);

	material = material_create(vector3f_create(1.f, 1.f, 1.0f), 0.f, 0.f);
	free_cap_texture(&material);
//	set_outline_texture(&material, "data/earth.ppm");
//	set_outline_texture(&material, "data/coca-cola.ppm");
//	set_cap_texture(&material, "data/can_top.ppm");
//	free_outline_texture(&material);
//	set_outline_checkerboard(&material, (t_vector2f){10.f, 6.f},
//								  vector3f_create(0, 0, 0));
//	set_cap_checkerboard(&material, (t_vector2f) {10.f, 10.f},
//						 vector3f_create(0, 0, 0));
//	object = sphere_create(vector3f_create(0.f, -3.f, 15.f), 1.5f, material);
	object = cylinder_create(vector3f_create(0.f, -3.f, 15.f), vector3f_create(0, 1, 0), (t_object_size){1, 1}, material);
	add_object(engine, object);

	material = material_create(vector3f_create(1.f, 1.f, 1.0f), 0.f, 0.f);
	set_outline_texture(&material, "data/textures/moon.ppm");
	object = sphere_create(vector3f_create(0.f, -3.f, 15.f), 1.5f, material);
//	add_object(engine, object);

	material = material_create(vector3f_create(1.f, 1.f, 1.0f), 0.f, 0.f);
	set_outline_texture(&material, "data/textures/2k_stars.ppm");
	object = sphere_create(vector3f_create(0.f, -3.f, 15.f), 1.5f, material);
//	add_object(engine, object);

	material = material_create(vector3f_create(0.0f, 0.0f, 0.0f), 0.f, 0.f);
//	set_outline_normals_map(&material, "data/normals_map.ppm");
//	set_outline_normals_map(&material, "data/earth_normals.ppm");
//	set_outline_texture(&material, "data/earth.ppm");
	material.reflection = 0.9f;
	object = sphere_create(vector3f_create(10.f, -5.f, 10.f), 3.f, material);
	add_object(engine, object);

	material = material_create(vector3f_create(1.f, 0.5f, 0.0f), 0.f, 0.f);
	material.specular = 0.5f;
	t_object_size size = (t_object_size){3, 5};
	object = cone_create(vector3f_create(-10.f, 0.f, 10.f), vector3f_create(0.f, 1.f, 0.f), size, material);
	add_object(engine, object);
	light = light_create(vector3f_create(0, 1, 15), vector3f_create(1, 1, 1), 1.f);

	add_light(engine, light);
//    t_object_size size = (t_object_size) {0.25f, 2.f};
	engine->scene.ambient_light = light_create(vector3f_create(0, 0, 0),
										vector3f_create(1, 1, 1), 0.5f);
	engine->scene.sky_color = vector3f_create(0, 0, 0);
}
