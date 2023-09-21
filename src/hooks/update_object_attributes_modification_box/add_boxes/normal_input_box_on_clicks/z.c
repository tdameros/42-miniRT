/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:16:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:32:02 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"
#include "hooks.h"
#include "events.h"

void	normal_input_box_z_on_click_plus(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_object			*object;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (normal_input_box_z_on_click_text(self, engine, click_data));
	object = engine->gui.selected_object.object;
	if (object == NULL)
		return ;
	object_rotate(object, (t_vector3f){0.f, 0.f, 1.f},
		engine->gui.object_rotation_degrees);
	engine->scene_changed = true;
	update_xyz_float_input_boxes(engine, object->axis_degrees,
		&engine->gui.float_input_boxes.normal);
	if (recalculate_bvh_scene(&engine->scene, object) < 0)
		ft_fatal_error("normal_input_box_z_on_click_plus: recalculate_bvh_scene failed");
}

void	normal_input_box_z_on_click_minus(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_object			*object;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (normal_input_box_z_on_click_text(self, engine, click_data));
	object = engine->gui.selected_object.object;
	if (object == NULL)
		return ;
	object_rotate(object, (t_vector3f){0.f, 0.f, 1.f},
		-engine->gui.object_rotation_degrees);
	engine->scene_changed = true;
	update_xyz_float_input_boxes(engine, object->axis_degrees,
		&engine->gui.float_input_boxes.normal);
	if (recalculate_bvh_scene(&engine->scene, object) < 0)
		ft_fatal_error("normal_input_box_z_on_click_minus: recalculate_bvh_scene failed");
}

void	normal_input_box_z_on_click_text(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	if (click_data.button == SCROLL_UP)
	{
		click_data.button = BUTTON_LEFT;
		return (normal_input_box_z_on_click_plus(self, engine, click_data));
	}
	if (click_data.button == SCROLL_DOWN)
	{
		click_data.button = BUTTON_LEFT;
		return (normal_input_box_z_on_click_minus(self, engine, click_data));
	}
}
