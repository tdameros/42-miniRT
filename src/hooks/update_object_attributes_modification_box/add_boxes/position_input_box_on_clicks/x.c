/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:13:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/03 00:13:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"
#include "hooks.h"
#include "events.h"

void	position_input_box_x_on_click_plus(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_object	*object;
	t_light		*light;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (position_input_box_x_on_click_text(self, engine, click_data));
	object = engine->gui.selected_object.object;
	light = engine->gui.selected_object.light;
	if (light != NULL)
	{
		engine->scene_changed = true;
		light->position.x += engine->gui.object_modification_amount;
		light_calculate_cache(light);
		update_xyz_float_input_boxes(engine, light->position,
			&engine->gui.float_input_boxes.position);
	}
	else if (object != NULL)
	{
		engine->scene_changed = true;
		object_move(object, (t_vector3f){1.f, 0.f, 0.f},
			engine->gui.object_modification_amount);
		update_xyz_float_input_boxes(engine, object->position,
			&engine->gui.float_input_boxes.position);
		if (recalculate_bvh_scene(&engine->scene, object) < 0)
			ft_fatal_error("position_input_box_x_on_click_plus: recalculate_bvh_scene failed");
	}
}

void	position_input_box_x_on_click_minus(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_object	*object;
	t_light		*light;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (position_input_box_x_on_click_text(self, engine, click_data));
	object = engine->gui.selected_object.object;
	light = engine->gui.selected_object.light;
	if (light != NULL)
	{
		engine->scene_changed = true;
		light->position.x -= engine->gui.object_modification_amount;
		light_calculate_cache(light);
		update_xyz_float_input_boxes(engine, light->position,
			&engine->gui.float_input_boxes.position);
	}
	else if (object != NULL)
	{
		engine->scene_changed = true;
		object_move(object, (t_vector3f){1.f, 0.f, 0.f},
			-engine->gui.object_modification_amount);
		update_xyz_float_input_boxes(engine, object->position,
			&engine->gui.float_input_boxes.position);
		if (recalculate_bvh_scene(&engine->scene, object) < 0)
			ft_fatal_error("position_input_box_x_on_click_minus: recalculate_bvh_scene failed");
	}
}

void	position_input_box_x_on_click_text(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	if (click_data.button == SCROLL_UP)
	{
		click_data.button = BUTTON_LEFT;
		return (position_input_box_x_on_click_plus(self, engine, click_data));
	}
	if (click_data.button == SCROLL_DOWN)
	{
		click_data.button = BUTTON_LEFT;
		return (position_input_box_x_on_click_minus(self, engine, click_data));
	}
}
