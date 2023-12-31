/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_texture_button.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:12:42 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 01:12:42 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "font/render.h"
#include "events.h"
#include "gui/optional_boxes.h"

#define CAP_TEXTURE_BUTTON_TEXT "Change textures"

static void	texture_button_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

void	add_texture_button(t_engine *engine, t_gui_box *gui_box,
			int *y, t_gui_box *parent)
{
	add_button_box(engine, gui_box, y, parent);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->image, CAP_TEXTURE_BUTTON_TEXT);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->on_hover_image, CAP_TEXTURE_BUTTON_TEXT);
	gui_box->on_click = &texture_button_on_click;
}

static void	texture_button_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->gui.current_optional_box == TEXTURE_BOX)
		engine->gui.current_optional_box = NO_OPTIONAL_BOX;
	else
		engine->gui.current_optional_box = TEXTURE_BOX;
}
