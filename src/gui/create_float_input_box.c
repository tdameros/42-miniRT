/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_float_input_box.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:55:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/02 17:55:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"
#include "gui/utils.h"

int	create_float_input_box(t_engine *engine, t_gui_box *gui_box,
		t_float_input_box_on_click on_click)
{
	if (create_horizontal_boxes(engine, gui_box, "20 60 20") < 0)
		return (-1);
	gui_box->children.data[0].on_click = on_click.minus;
	gui_box->children.data[1].on_click = on_click.text_box;
	gui_box->children.data[2].on_click = on_click.plus;
	gui_box->children.data[0].draw = &default_gui_box_draw;
	gui_box->children.data[1].draw = &default_gui_box_draw;
	gui_box->children.data[2].draw = &default_gui_box_draw;
	change_image_color(&gui_box->children.data[0].image, COLOR_DARK_GRASS);
	change_image_color(&gui_box->children.data[1].image, COLOR_WHITE);
	change_image_color(&gui_box->children.data[2].image, COLOR_DARK_GRASS);
	return (0);
}
