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

#include "engine.h"
#include "gui/box.h"
#include "events.h"
#include "hooks.h"

void	outline_checkerboard_size_input_box_x_on_click_plus(t_gui_box *self,
			t_engine *engine, t_click_data click_data)
{
	t_object			*object;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (outline_checkerboard_size_input_box_x_on_click_text(self,
				engine, click_data));
	object = engine->gui.selected_object.object;
	if (object == NULL)
		return ;
	object->material.texture.outline_checkerboard.size.x++;
	engine->scene_changed = true;
	update_xy_float_input_boxes(engine,
		object->material.texture.outline_checkerboard.size,
		&engine->gui.float_input_boxes.checkered_pattern_size);
	redraw_icons(engine, engine->gui.selected_object.object->material);
}

void	outline_checkerboard_size_input_box_x_on_click_minus(t_gui_box *self,
			t_engine *engine, t_click_data click_data)
{
	t_object			*object;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (outline_checkerboard_size_input_box_x_on_click_text(self,
				engine, click_data));
	object = engine->gui.selected_object.object;
	if (object == NULL || object->material.texture.outline_checkerboard.size.x
		<= 1.f)
		return ;
	object->material.texture.outline_checkerboard.size.x--;
	engine->scene_changed = true;
	update_xy_float_input_boxes(engine,
		object->material.texture.outline_checkerboard.size,
		&engine->gui.float_input_boxes.checkered_pattern_size);
	redraw_icons(engine, engine->gui.selected_object.object->material);
}

void	outline_checkerboard_size_input_box_x_on_click_text(
			t_gui_box *self, t_engine *engine, t_click_data click_data)
{
	if (click_data.button == SCROLL_UP)
	{
		click_data.button = BUTTON_LEFT;
		return (outline_checkerboard_size_input_box_x_on_click_plus(self,
				engine, click_data));
	}
	if (click_data.button == SCROLL_DOWN)
	{
		click_data.button = BUTTON_LEFT;
		return (outline_checkerboard_size_input_box_x_on_click_minus(self,
				engine, click_data));
	}
}
