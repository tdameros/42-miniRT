/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_outline_checkerboard_size_box.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:12:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/23 19:12:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "hooks.h"
#include "font/render.h"

int	add_outline_checkerboard_size_box(t_engine *engine, t_gui_box *gui_box,
		int *i, t_gui_box *parent)
{
	if (add_x_y_box(engine, gui_box, i, parent) < 0)
		return (-1);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[0].image, "Outline checkerboard size");
	get_x_y_input_box(gui_box, 'x', '-')->on_click \
		= &outline_checkerboard_size_input_box_x_on_click_plus;
	get_x_y_input_box(gui_box, 'x', 't')->on_click \
		= &outline_checkerboard_size_input_box_x_on_click_text;
	get_x_y_input_box(gui_box, 'x', '+')->on_click \
		= &outline_checkerboard_size_input_box_x_on_click_plus;
	get_x_y_input_box(gui_box, 'x', 'd')->on_click \
		= &outline_checkerboard_size_input_box_x_on_click_text;
	engine->gui.float_input_boxes.checkered_pattern_size.x
		= get_x_y_input_box(gui_box, 'x', 'b');
	get_x_y_input_box(gui_box, 'y', '-')->on_click \
		= &outline_checkerboard_size_input_box_y_on_click_minus;
	get_x_y_input_box(gui_box, 'y', 't')->on_click \
		= &outline_checkerboard_size_input_box_y_on_click_text;
	get_x_y_input_box(gui_box, 'y', '+')->on_click \
		= &outline_checkerboard_size_input_box_y_on_click_plus;
	get_x_y_input_box(gui_box, 'y', 'd')->on_click \
		= &outline_checkerboard_size_input_box_y_on_click_text;
	engine->gui.float_input_boxes.checkered_pattern_size.y
		= get_x_y_input_box(gui_box, 'y', 'b');
	return (0);
}
