/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation_on_clicks.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:59:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/07 09:59:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "object.h"
#include "events.h"
#include "hooks.h"
#include "ray_tracer_gui_api.h"

void	sphere_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_material	material;
	t_object	object;

	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	ft_bzero(&material, sizeof(material));
	if (material_deep_copy(&material,
			&engine->gui.color_and_material.material_to_assign_to_new_objects)
		< 0)
		return ((void)ft_print_error("Warning: Failed to create new sphere, "
				"material allocation failed\n"));
	object = sphere_create(vector3f_create(0, 0, 0), 0.5f, material);
	add_object(engine, object);
	engine->object_being_placed_distance = DEFAULT_DISTANCE_OF_NEW_OBJECTS;
	engine->object_being_placed.object
		= &engine->scene.objects.data[engine->scene.objects.length - 1];
	update_object_attributes_modification_box(engine);
	(void)self;
}

void	plane_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_material	material;
	t_object	object;

	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	ft_bzero(&material, sizeof(material));
	if (material_deep_copy(&material,
			&engine->gui.color_and_material.material_to_assign_to_new_objects)
		< 0)
		return ((void)ft_print_error("Warning: Failed to create new plane, "
				"material allocation failed\n"));
	object = plane_create(vector3f_create(0, 0, 0), (t_vector3f){0, 1, 0},
			material);
	add_object(engine, object);
	engine->object_being_placed_distance = DEFAULT_DISTANCE_OF_NEW_OBJECTS;
	engine->object_being_placed.object
		= &engine->scene.objects.data[engine->scene.objects.length - 1];
	update_object_attributes_modification_box(engine);
	(void)self;
}

void	cylinder_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_material			material;
	const t_object_size	size = (t_object_size){0.5f, 3.f};
	t_object			object;

	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	ft_bzero(&material, sizeof(material));
	if (material_deep_copy(&material,
			&engine->gui.color_and_material.material_to_assign_to_new_objects)
		< 0)
		return ((void)ft_print_error("Warning: Failed to create new cylinder, "
				"material allocation failed\n"));
	object = cylinder_create(vector3f_create(0, 0, 0), (t_vector3f){0, 1, 0},
			size, material);
	add_object(engine, object);
	engine->object_being_placed_distance = DEFAULT_DISTANCE_OF_NEW_OBJECTS;
	engine->object_being_placed.object
		= &engine->scene.objects.data[engine->scene.objects.length - 1];
	update_object_attributes_modification_box(engine);
	(void)self;
}

void	cone_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_material			material;
	const t_object_size	size = (t_object_size){1.f, 3.f};
	t_object			object;

	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	ft_bzero(&material, sizeof(material));
	if (material_deep_copy(&material,
			&engine->gui.color_and_material.material_to_assign_to_new_objects)
		< 0)
		return ((void)ft_print_error("Warning: Failed to create new cone, "
				"material allocation failed\n"));
	object = cone_create(vector3f_create(0, 0, 0), (t_vector3f){0, 1, 0}, size,
			material);
	add_object(engine, object);
	engine->object_being_placed_distance = DEFAULT_DISTANCE_OF_NEW_OBJECTS;
	engine->object_being_placed.object
		= &engine->scene.objects.data[engine->scene.objects.length - 1];
	update_object_attributes_modification_box(engine);
	(void)self;
}

void	mesh_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->gui.current_optional_box == MESH_OBJECT_CREATION_BOX)
		engine->gui.current_optional_box = NO_OPTIONAL_BOX;
	else
		engine->gui.current_optional_box = MESH_OBJECT_CREATION_BOX;
}

void	light_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	const t_vector3f	light_color = engine->gui.color_and_material.\
			material_to_assign_to_new_objects.albedo;
	t_light				light;

	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	light = light_create(vector3f_create(0, 0, 0), light_color, 0.5f);
	add_light(engine, light);
	engine->object_being_placed_distance = DEFAULT_DISTANCE_OF_NEW_OBJECTS;
	engine->object_being_placed.light
		= &engine->scene.lights.data[engine->scene.lights.length - 1];
	update_object_attributes_modification_box(engine);
	(void)self;
}
