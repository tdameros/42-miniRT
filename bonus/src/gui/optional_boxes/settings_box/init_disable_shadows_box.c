/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_disable_shadows_box.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:37:05 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:37:05 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "engine.h"
#include "events.h"
#include "font/render.h"
#include "gui/box.h"

static void	antialiasing_toggle_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

void	init_disable_shadows_box(t_engine *engine, t_gui_box *gui_box,
			int *y, t_gui_box *parent)
{
	add_toggle_box(engine, gui_box, y, parent);
	draw_toggle_box(gui_box->children.data + 0, engine->antialiasing);
	change_image_color(&gui_box->children.data[1].image, COLOR_TRANSPARENT);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[1].image, "Shadows");
	gui_box->children.data->on_click = &antialiasing_toggle_box_on_click;
}

static void	antialiasing_toggle_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return ;
	engine->scene.render_shadows = !engine->scene.render_shadows;
	engine->scene_changed = true;
	draw_toggle_box(self, engine->scene.render_shadows);
}
