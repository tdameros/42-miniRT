/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_scale_box.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 05:16:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:34:26 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"
#include "hooks.h"
#include "font/render.h"

static void	init_y_buttons(t_engine *engine, t_gui_box *gui_box);
static void	init_x_buttons(t_engine *engine, t_gui_box *gui_box);
static void	init_z_buttons(t_engine *engine, t_gui_box *gui_box);

void	add_scale_box(t_engine *engine, t_gui_box *gui_box, int *i,
			t_gui_box *parent)
{
	add_x_y_z_box(engine, gui_box, i, parent);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[0].image, "Scale");
	init_x_buttons(engine, gui_box);
	init_y_buttons(engine, gui_box);
	init_z_buttons(engine, gui_box);
}

static void	init_x_buttons(t_engine *engine, t_gui_box *gui_box)
{
	get_x_y_z_input_box(gui_box, 'x', '-')->on_click \
		= &scale_input_box_x_on_click_minus;
	get_x_y_z_input_box(gui_box, 'x', 't')->on_click \
		= &scale_input_box_x_on_click_text;
	get_x_y_z_input_box(gui_box, 'x', '+')->on_click \
		= &scale_input_box_x_on_click_plus;
	get_x_y_z_input_box(gui_box, 'x', 'd')->on_click \
		= &scale_input_box_x_on_click_text;
	engine->gui.float_input_boxes.scale.x
		= get_x_y_z_input_box(gui_box, 'x', 'b');
}

static void	init_y_buttons(t_engine *engine, t_gui_box *gui_box)
{
	get_x_y_z_input_box(gui_box, 'y', '-')->on_click \
		= &scale_input_box_y_on_click_minus;
	get_x_y_z_input_box(gui_box, 'y', 't')->on_click \
		= &scale_input_box_y_on_click_text;
	get_x_y_z_input_box(gui_box, 'y', '+')->on_click \
		= &scale_input_box_y_on_click_plus;
	get_x_y_z_input_box(gui_box, 'y', 'd')->on_click \
		= &scale_input_box_y_on_click_text;
	engine->gui.float_input_boxes.scale.y
		= get_x_y_z_input_box(gui_box, 'y', 'b');
}

static void	init_z_buttons(t_engine *engine, t_gui_box *gui_box)
{
	get_x_y_z_input_box(gui_box, 'z', '-')->on_click \
		= &scale_input_box_z_on_click_minus;
	get_x_y_z_input_box(gui_box, 'z', 't')->on_click \
		= &scale_input_box_z_on_click_text;
	get_x_y_z_input_box(gui_box, 'z', '+')->on_click \
		= &scale_input_box_z_on_click_plus;
	get_x_y_z_input_box(gui_box, 'z', 'd')->on_click \
		= &scale_input_box_z_on_click_text;
	engine->gui.float_input_boxes.scale.z
		= get_x_y_z_input_box(gui_box, 'z', 'b');
}
