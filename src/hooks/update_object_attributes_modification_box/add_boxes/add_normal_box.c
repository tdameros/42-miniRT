/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_normal_box.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 05:16:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/03 05:16:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"
#include "hooks.h"
#include "font/render.h"

int	add_normal_box(t_engine *engine, t_gui_box *gui_box, int *i,
		t_gui_box *parent)
{
	if (add_x_y_z_box(engine, gui_box, i, parent) < 0)
		return (-1);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[0].image, "Rotation");
	get_x_y_z_input_box(gui_box, 'x', '-')->on_click \
		= &normal_input_box_x_on_click_minus;
	get_x_y_z_input_box(gui_box, 'x', '+')->on_click \
		= &normal_input_box_x_on_click_plus;
	get_x_y_z_input_box(gui_box, 'y', '-')->on_click \
		= &normal_input_box_y_on_click_minus;
	get_x_y_z_input_box(gui_box, 'y', '+')->on_click \
		= &normal_input_box_y_on_click_plus;
	get_x_y_z_input_box(gui_box, 'z', '-')->on_click \
		= &normal_input_box_z_on_click_minus;
	get_x_y_z_input_box(gui_box, 'z', '+')->on_click \
		= &normal_input_box_z_on_click_plus;
	return (0);
}
