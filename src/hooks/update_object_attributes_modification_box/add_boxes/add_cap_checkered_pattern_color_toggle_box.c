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

static void	cap_checkerboard_color_toggle_box_on_click(t_gui_box *self,
				t_engine *engine, t_click_data click_data);

void	add_cap_checkerboard_color_toggle_box(t_engine *engine,
			t_gui_box *gui_box, int *i, t_gui_box *parent)
{
	t_object	*object;

	engine->gui.color_and_material.color_being_changed = BASE_COLOR;
	object = engine->gui.selected_object.object;
	if (object != NULL
		&& object->material.textures.cap.texture_type != PPM_TEXTURE
		&& object->material.textures.cap.checkerboard.size.y <= 1.f
		&& object->material.textures.cap.checkerboard.size.x <= 1.f)
		object->material.textures.cap.texture_type = NONE;
	else if (object != NULL
		&& object->material.textures.cap.texture_type != PPM_TEXTURE)
		object->material.textures.cap.texture_type = CHECKERBOARD;
	add_toggle_box(engine, gui_box, i, parent);
	gui_box->children.data->on_click
		= &cap_checkerboard_color_toggle_box_on_click;
	engine->gui.color_and_material.cap_checkered_pattern_color_toggle_box
		= gui_box->children.data;
	draw_toggle_box(gui_box->children.data,
		engine->gui.color_and_material.color_being_changed \
		== CAP_CHECKERBOARD_COLOR);
	change_image_color(&gui_box->children.data[1].image, COLOR_TRANSPARENT);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[1].image, "Change cap checkerboard color");
}

static void	cap_checkerboard_color_toggle_box_on_click(t_gui_box *self,
				t_engine *engine, t_click_data click_data)
{
	const t_object				*object = engine->gui.selected_object.object;
	enum e_color_being_changed	*color_being_changed;

	color_being_changed = &engine->gui.color_and_material.color_being_changed;
	if (click_data.button != BUTTON_LEFT || object == NULL)
		return ;
	if (*color_being_changed == CAP_CHECKERBOARD_COLOR
		|| object->material.textures.cap.texture_type != CHECKERBOARD)
		*color_being_changed = BASE_COLOR;
	else
		*color_being_changed = CAP_CHECKERBOARD_COLOR;
	draw_toggle_box(engine->gui.color_and_material.\
		outline_checkered_pattern_color_toggle_box,
		*color_being_changed == OUTLINE_CHECKERBOARD_COLOR);
	draw_toggle_box(self, *color_being_changed == CAP_CHECKERBOARD_COLOR);
	engine->scene_changed = true;
}
