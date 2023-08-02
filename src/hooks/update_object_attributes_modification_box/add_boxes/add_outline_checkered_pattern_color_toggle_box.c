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

#include <float.h>
#include "engine.h"
#include "gui/box.h"
#include "gui/UI.h"
#include "hooks.h"
#include "font/render.h"
#include "events.h"

static void	outline_checkerboard_color_toggle_box_on_click(t_gui_box *self,
				t_engine *engine, t_click_data click_data);

void	add_outline_checkerboard_color_toggle_box(t_engine *engine,
			t_gui_box *gui_box, int *i, t_gui_box *parent)
{
	t_object	*object;

	engine->gui.color_and_material.color_being_changed = BASE_COLOR;
	object = engine->gui.selected_object.object;
	if (object != NULL
		&& object->material.texture.outline.texture_type != PPM_TEXTURE
		&& object->material.texture.outline.checkerboard.size.y <= 1.f
		&& object->material.texture.outline.checkerboard.size.x <= 1.f)
		object->material.texture.outline.texture_type = NONE;
	else if (object != NULL
		&& object->material.texture.outline.texture_type != PPM_TEXTURE)
		object->material.texture.outline.texture_type = CHECKERBOARD;
	add_toggle_box(engine, gui_box, i, parent);
	gui_box->children.data->on_click
		= &outline_checkerboard_color_toggle_box_on_click;
	engine->gui.color_and_material.outline_checkered_pattern_color_toggle_box
		= gui_box->children.data;
	draw_outline_checkerboard_color_toggle_box(gui_box->children.data, engine);
	change_image_color(&gui_box->children.data[1].image, COLOR_TRANSPARENT);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[1].image, "Change outline checkerboard color");
}

static void	outline_checkerboard_color_toggle_box_on_click(t_gui_box *self,
				t_engine *engine, t_click_data click_data)
{
	t_object	*object;

	object = engine->gui.selected_object.object;
	if (click_data.button != BUTTON_LEFT || object == NULL)
		return ;
	if (engine->gui.color_and_material.color_being_changed == OUTLINE_COLOR
		|| object->material.texture.outline.texture_type != CHECKERBOARD)
		engine->gui.color_and_material.color_being_changed = BASE_COLOR;
	else
		engine->gui.color_and_material.color_being_changed = OUTLINE_COLOR;
	draw_outline_checkerboard_color_toggle_box(self, engine);
	draw_cap_checkerboard_color_toggle_box(
		engine->gui.color_and_material.cap_checkered_pattern_color_toggle_box,
		engine);
	engine->scene_changed = true;
}

void	draw_outline_checkerboard_color_toggle_box(
			t_gui_box *outline_checkerboard_color_toggle_box, t_engine *engine)
{
	if (outline_checkerboard_color_toggle_box == NULL)
		return ;
	change_image_color(&outline_checkerboard_color_toggle_box->image,
		COLOR_TRANSPARENT);
	change_image_color(&outline_checkerboard_color_toggle_box->on_hover_image,
		HOVER_GUI_COLOR);
	if (engine->gui.color_and_material.color_being_changed == OUTLINE_COLOR)
	{
		image_draw_check_mark(&outline_checkerboard_color_toggle_box->image,
			COLOR_WHITE, TOGGLE_BOX_BUTTON_OUTLINE_WIDTH);
		image_draw_check_mark(
			&outline_checkerboard_color_toggle_box->on_hover_image, COLOR_WHITE,
			TOGGLE_BOX_BUTTON_OUTLINE_WIDTH);
	}
	image_draw_outline(&outline_checkerboard_color_toggle_box->image,
		TOGGLE_BOX_BUTTON_OUTLINE_WIDTH, COLOR_BLACK);
	image_draw_outline(&outline_checkerboard_color_toggle_box->on_hover_image,
		TOGGLE_BOX_BUTTON_OUTLINE_WIDTH, COLOR_BLACK);
}
