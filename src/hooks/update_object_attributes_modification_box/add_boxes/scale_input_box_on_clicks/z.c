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

void	scale_input_box_z_on_click_plus(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_object			*object;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (scale_input_box_z_on_click_text(self, engine, click_data));
	object = engine->gui.selected_object.object;
	if (object == NULL || object->type != MESH)
		return ;
	object->cache.mesh.scale_vector.z += engine->gui.object_modification_amount;
	mesh_object_set_scale(object, object->cache.mesh.scale_vector);
	engine->scene_changed = true;
	update_xyz_float_input_boxes(engine, object->cache.mesh.scale_vector,
		&engine->gui.float_input_boxes.scale);
}

void	scale_input_box_z_on_click_minus(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_object			*object;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (scale_input_box_z_on_click_text(self, engine, click_data));
	object = engine->gui.selected_object.object;
	if (object == NULL || object->type != MESH)
		return ;
	object->cache.mesh.scale_vector.z -= engine->gui.object_modification_amount;
	mesh_object_set_scale(object, object->cache.mesh.scale_vector);
	engine->scene_changed = true;
	update_xyz_float_input_boxes(engine, object->cache.mesh.scale_vector,
		&engine->gui.float_input_boxes.scale);
}

void	scale_input_box_z_on_click_text(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	if (click_data.button == SCROLL_UP)
	{
		click_data.button = BUTTON_LEFT;
		return (scale_input_box_z_on_click_plus(self, engine, click_data));
	}
	if (click_data.button == SCROLL_DOWN)
	{
		click_data.button = BUTTON_LEFT;
		return (scale_input_box_z_on_click_minus(self, engine, click_data));
	}
}
