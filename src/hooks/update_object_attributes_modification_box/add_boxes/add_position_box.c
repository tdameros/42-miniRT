/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_position_box.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:24:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:36:37 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "gui/box.h"
#include "gui/utils.h"
#include "hooks.h"
#include "font/render.h"

static void	init_y_buttons(t_engine *engine, t_gui_box *gui_box);
static void	init_x_buttons(t_engine *engine, t_gui_box *gui_box);
static void	init_z_buttons(t_engine *engine, t_gui_box *gui_box);

void	add_position_box(t_engine *engine, t_gui_box *gui_box, int *i,
			t_gui_box *parent)
{
	add_x_y_z_box(engine, gui_box, i, parent);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[0].image, "Position");
	init_x_buttons(engine, gui_box);
	init_y_buttons(engine, gui_box);
	init_z_buttons(engine, gui_box);
}

static void	init_x_buttons(t_engine *engine, t_gui_box *gui_box)
{
	get_x_y_z_input_box(gui_box, 'x', '-')->on_click \
		= &position_input_box_x_on_click_minus;
	get_x_y_z_input_box(gui_box, 'x', 't')->on_click \
		= &position_input_box_x_on_click_text;
	get_x_y_z_input_box(gui_box, 'x', '+')->on_click \
		= &position_input_box_x_on_click_plus;
	get_x_y_z_input_box(gui_box, 'x', 'd')->on_click \
		= &position_input_box_x_on_click_text;
	engine->gui.float_input_boxes.position.x
		= get_x_y_z_input_box(gui_box, 'x', 'b');
}

static void	init_y_buttons(t_engine *engine, t_gui_box *gui_box)
{
	get_x_y_z_input_box(gui_box, 'y', '-')->on_click \
		= &position_input_box_y_on_click_minus;
	get_x_y_z_input_box(gui_box, 'y', 't')->on_click \
		= &position_input_box_y_on_click_text;
	get_x_y_z_input_box(gui_box, 'y', '+')->on_click \
		= &position_input_box_y_on_click_plus;
	get_x_y_z_input_box(gui_box, 'y', 'd')->on_click \
		= &position_input_box_y_on_click_text;
	engine->gui.float_input_boxes.position.y
		= get_x_y_z_input_box(gui_box, 'y', 'b');
}

static void	init_z_buttons(t_engine *engine, t_gui_box *gui_box)
{
	get_x_y_z_input_box(gui_box, 'z', '-')->on_click \
		= &position_input_box_z_on_click_minus;
	get_x_y_z_input_box(gui_box, 'z', 't')->on_click \
		= &position_input_box_z_on_click_text;
	get_x_y_z_input_box(gui_box, 'z', '+')->on_click \
		= &position_input_box_z_on_click_plus;
	get_x_y_z_input_box(gui_box, 'z', 'd')->on_click \
		= &position_input_box_z_on_click_text;
	engine->gui.float_input_boxes.position.z
		= get_x_y_z_input_box(gui_box, 'z', 'b');
}
