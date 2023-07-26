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

#define DEFAULT_DISTANCE 10.f

void	sphere_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	const t_material	material
		= engine->gui.material_to_assign_to_new_objects;
	t_object			object;

	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	object = sphere_create(vector3f_create(0, 0, 0), 0.5f, material);
	if (add_object(engine, object) < 0)
	{
		ft_print_error("Failed to create new sphere\n");
		return ;
	}
	engine->object_being_placed_distance = DEFAULT_DISTANCE;
	engine->object_being_placed.object = engine->scene.objects.data
		+ engine->scene.objects.length - 1;
	update_object_attributes_modification_box(engine);
	(void)self;
}

void	plane_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	const t_material	material
		= engine->gui.material_to_assign_to_new_objects;
	t_object			object;

	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	object = plane_create(vector3f_create(0, 0, 0),
			vector3f_multiply(engine->camera.direction, -1.f), material);
	if (add_object(engine, object) < 0)
	{
		ft_print_error("Failed to create new plane\n");
		return ;
	}
	engine->object_being_placed_distance = DEFAULT_DISTANCE;
	engine->object_being_placed.object = engine->scene.objects.data
		+ engine->scene.objects.length - 1;
	update_object_attributes_modification_box(engine);
	(void)self;
}

void	cylinder_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	const t_material	material
		= engine->gui.material_to_assign_to_new_objects;
	const t_object_size	size = (t_object_size){0.5f, 3.f};
	t_object			object;

	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	object = cylinder_create(vector3f_create(0, 0, 0),
			vector3f_rotate_y(engine->camera.direction, 90), size, material);
	if (add_object(engine, object) < 0)
	{
		ft_print_error("Failed to create new cylinder\n");
		return ;
	}
	engine->object_being_placed_distance = DEFAULT_DISTANCE;
	engine->object_being_placed.object = engine->scene.objects.data
		+ engine->scene.objects.length - 1;
	update_object_attributes_modification_box(engine);
	(void)self;
}

void	cone_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	const t_material	material
		= engine->gui.material_to_assign_to_new_objects;
	const t_object_size	size = (t_object_size){1.f, 3.f};
	t_object			object;

	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	object = cone_create(vector3f_create(0, 0, 0),
			vector3f_rotate_x(engine->camera.direction, 90), size, material);
	if (add_object(engine, object) < 0)
	{
		ft_print_error("Failed to create new cone\n");
		return ;
	}
	engine->object_being_placed_distance = DEFAULT_DISTANCE;
	engine->object_being_placed.object = engine->scene.objects.data
		+ engine->scene.objects.length - 1;
	update_object_attributes_modification_box(engine);
	(void)self;
}

void	light_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_light	light;

	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	light = light_create(vector3f_create(0, 0, 0),
			engine->gui.material_to_assign_to_new_objects.albedo,
			0.5f);
	if (add_light(engine, light) < 0)
	{
		ft_print_error("Failed to create new light\n");
		return ;
	}
	engine->object_being_placed_distance = DEFAULT_DISTANCE;
	engine->object_being_placed.light = engine->scene.lights.data
		+ engine->scene.lights.length - 1;
	update_object_attributes_modification_box(engine);
	(void)self;
}
