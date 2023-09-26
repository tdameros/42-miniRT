/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_reset_camera_peaking_box.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:36:55 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:36:56 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "font/render.h"
#include "gui/box.h"
#include "gui/optional_boxes.h"
#include "events.h"

#define BUTTON_MESSAGE "Reset camera peaking"

static void	reset_camera_peaking_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

void	init_reset_camera_peaking_box(t_engine *engine, t_gui_box *gui_box,
			int *y, t_gui_box *parent)
{
	add_button_box(engine, gui_box, y, parent);
	write_centered_string_to_image(&engine->gui.font, &gui_box->image,
		BUTTON_MESSAGE);
	write_centered_string_to_image(&engine->gui.font, &gui_box->on_hover_image,
		BUTTON_MESSAGE);
	gui_box->on_click = &reset_camera_peaking_box_on_click;
}

static void	reset_camera_peaking_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return ;
	engine->camera.up_vector = (t_vector3f){0, 1, 0};
	camera_recalculate_projection(&engine->camera);
	camera_recalculate_view(&engine->camera);
	camera_recalculate_rays(&engine->camera);
	engine->scene_changed = true;
}
