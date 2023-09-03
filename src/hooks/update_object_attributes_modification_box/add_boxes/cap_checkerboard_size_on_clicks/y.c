/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:15:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/03 00:15:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "events.h"
#include "hooks.h"

void	cap_checkerboard_size_input_box_y_on_click_plus(t_gui_box *self,
			t_engine *engine, t_click_data click_data)
{
	t_object	*object;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (cap_checkerboard_size_input_box_y_on_click_text(self,
				engine, click_data));
	object = engine->gui.selected_object.object;
	if (object == NULL)
		return ;
	if ((int)object->material.texture.cap.checkerboard.size.y % 2)
		object->material.texture.cap.checkerboard.size.y++;
	object->material.texture.cap.checkerboard.size.y
		= (int)object->material.texture.cap.checkerboard.size.y + 2;
	if (object->material.texture.cap.texture_type == TEXTURE)
		free_cap_texture(&object->material);
	object->material.texture.cap.texture_type = CHECKERBOARD;
	engine->scene_changed = true;
	update_xy_float_input_boxes(engine,
		vector2f_divide(object->material.texture.cap.checkerboard.size, 2.f),
		&engine->gui.float_input_boxes.cap_checkerboard_size);
	redraw_icons(engine, engine->gui.selected_object.object->material);
}

void	cap_checkerboard_size_input_box_y_on_click_minus(t_gui_box *self,
			t_engine *engine, t_click_data click_data)
{
	t_object			*object;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (cap_checkerboard_size_input_box_y_on_click_text(self,
				engine, click_data));
	object = engine->gui.selected_object.object;
	if (object == NULL || object->material.texture.cap.checkerboard.size.y
		<= 1.f)
		return ;
	if ((int)object->material.texture.cap.checkerboard.size.y % 2)
		object->material.texture.cap.checkerboard.size.y++;
	object->material.texture.cap.checkerboard.size.y
		= (int)object->material.texture.cap.checkerboard.size.y - 2;
	if (object->material.texture.cap.checkerboard.size.x <= 1.f
		&& object->material.texture.cap.checkerboard.size.y <= 1.f)
	{
		object->material.texture.cap.texture_type = NONE;
		if (engine->gui.color_and_material.color_being_changed == CAP_CHECKERBOARD_COLOR)
		{
			engine->gui.color_and_material.color_being_changed = BASE_COLOR;
			draw_toggle_box(
				engine->gui.color_and_material.\
				cap_checkered_pattern_color_toggle_box, false);
		}
	}
	engine->scene_changed = true;
	update_xy_float_input_boxes(engine,
		vector2f_divide(object->material.texture.cap.checkerboard.size, 2.f),
		&engine->gui.float_input_boxes.cap_checkerboard_size);
	redraw_icons(engine, engine->gui.selected_object.object->material);
}

void	cap_checkerboard_size_input_box_y_on_click_text(t_gui_box *self,
			t_engine *engine, t_click_data click_data)
{
	if (click_data.button == SCROLL_UP)
	{
		click_data.button = BUTTON_LEFT;
		return (cap_checkerboard_size_input_box_y_on_click_plus(self,
				engine, click_data));
	}
	if (click_data.button == SCROLL_DOWN)
	{
		click_data.button = BUTTON_LEFT;
		return (cap_checkerboard_size_input_box_y_on_click_minus(self,
				engine, click_data));
	}
}
