/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_checkered_pattern_color_toggle_box.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:46:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/23 16:46:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "gui/UI.h"
#include "hooks.h"
#include "font/render.h"
#include "events.h"

int	add_checkered_pattern_color_toggle_box(t_engine *engine, t_gui_box *gui_box,
		int *i, t_gui_box *parent)
{
	if (engine->gui.selected_object.object == NULL
		|| engine->gui.selected_object.object->material.texture.outline_type != CHECKERBOARD)
		engine->gui.color_being_changed_is_checked_pattern = false;
	if (add_toggle_box(engine, gui_box, i, parent) < 0)
		return (-1);
	change_image_color(&gui_box->children.data->image, COLOR_TRANSPARENT);
	if (engine->gui.color_being_changed_is_checked_pattern)
		image_draw_check_mark(&gui_box->children.data->image, COLOR_WHITE,
			TOGGLE_BOX_BUTTON_OUTLINE_WIDTH);
	image_draw_outline(&gui_box->children.data->image,
		TOGGLE_BOX_BUTTON_OUTLINE_WIDTH, COLOR_BLACK);
	change_image_color(&gui_box->children.data->on_hover_image,
		HOVER_GUI_COLOR);
	if (engine->gui.color_being_changed_is_checked_pattern)
		image_draw_check_mark(&gui_box->children.data->on_hover_image,
			COLOR_WHITE, TOGGLE_BOX_BUTTON_OUTLINE_WIDTH);
	image_draw_outline(&gui_box->children.data->on_hover_image,
		TOGGLE_BOX_BUTTON_OUTLINE_WIDTH, COLOR_BLACK);
	change_image_color(&gui_box->children.data[1].image, COLOR_TRANSPARENT);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[1].image, "Change checked pattern color");
	gui_box->children.data->on_click
		= &checkered_pattern_color_toggle_box_on_click;
	engine->gui.checkered_pattern_color_toggle_box = gui_box->children.data;
	return (0);
}

void	checkered_pattern_color_toggle_box_on_click(t_gui_box *self,
			t_engine *engine, t_click_data click_data)
{
	t_object	*object;

	object = engine->gui.selected_object.object;
	if (click_data.button != BUTTON_LEFT || object == NULL)
		return ;
	engine->gui.color_being_changed_is_checked_pattern
		= (! engine->gui.color_being_changed_is_checked_pattern
			&& object->material.texture.outline_type == CHECKERBOARD);
	change_image_color(&self->image, COLOR_TRANSPARENT);
	if (engine->gui.color_being_changed_is_checked_pattern)
		image_draw_check_mark(&self->image, COLOR_WHITE,
			TOGGLE_BOX_BUTTON_OUTLINE_WIDTH);
	image_draw_outline(&self->image, TOGGLE_BOX_BUTTON_OUTLINE_WIDTH,
		COLOR_BLACK);
	change_image_color(&self->on_hover_image, HOVER_GUI_COLOR);
	if (engine->gui.color_being_changed_is_checked_pattern)
		image_draw_check_mark(&self->on_hover_image, COLOR_WHITE,
			TOGGLE_BOX_BUTTON_OUTLINE_WIDTH);
	image_draw_outline(&self->on_hover_image, TOGGLE_BOX_BUTTON_OUTLINE_WIDTH,
		COLOR_BLACK);
	engine->scene_changed = true;
}
