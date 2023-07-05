/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_position_box.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:24:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/01 13:24:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "gui/box.h"
#include "gui/utils.h"
#include "hooks.h"
#include "gui/UI.h"
#include "font/render.h"

static int	init_x_y_z_box_children(t_engine *engine, t_gui_box *gui_box);
static int	add_x_y_z_buttons(t_engine *engine, t_gui_box *gui_box);
static int	init_x_y_z_buttons_children(t_engine *engine,
				t_gui_box *gui_box);
static int	create_x_y_z_input_box(t_engine *engine, t_gui_box *gui_box,
				const char *type);

int	add_x_y_z_box(t_engine *engine, t_gui_box *gui_box, int *i,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, parent, \
		(t_vector2i){
			.x = 0,
			.y = *i}, \
		(t_vector2i){
			.x = parent->size.x,
			.y = 75});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	*i += gui_box->size.y + 8;
	if (init_x_y_z_box_children(engine, gui_box) < 0)
	{
		destroy_t_image(&engine->window, &gui_box->image);
		ft_bzero(gui_box, sizeof(*gui_box));
		return (-1);
	}
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, 10);
	return (0);
}

static int	init_x_y_z_box_children(t_engine *engine, t_gui_box *gui_box)
{
	// TODO leaks
	if (create_vertical_boxes(engine, gui_box, "40 60", 0) < 0)
		return (-1);
	if (add_x_y_z_buttons(engine, gui_box->children.data + 1) < 0)
		return (-1);
	change_image_color(&gui_box->children.data[0].image, COLOR_TRANSPARENT);
	return (0);
}

static int	add_x_y_z_buttons(t_engine *engine, t_gui_box *gui_box)
{
	if (init_x_y_z_buttons_children(engine, gui_box) < 0)
	{
		destroy_t_image(&engine->window, &gui_box->image);
		ft_bzero(gui_box, sizeof(*gui_box));
		return (-1);
	}
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	round_image_corners(&gui_box->image, 10);
	return (0);
}

static int	init_x_y_z_buttons_children(t_engine *engine, t_gui_box *gui_box)
{
	// TODO leaks
	if (create_n_horizontal_boxes(engine, gui_box, 3,
			(t_boxes_offsets){4, 0}) < 0)
		return (ft_print_error("create n horizontal box failed"), -1);
	if (create_x_y_z_input_box(engine, gui_box->children.data + 0, "x") < 0)
		return (-1);
	if (create_x_y_z_input_box(engine, gui_box->children.data + 1, "y") < 0)
		return (-1);
	if (create_x_y_z_input_box(engine, gui_box->children.data + 2, "z") < 0)
		return (-1);
	return (0);
}

static int	create_x_y_z_input_box(t_engine *engine, t_gui_box *gui_box,
				const char *type)
{
	// TODO leaks
	if (create_vertical_boxes(engine, gui_box, "40 55 5", 0) < 0)
		return (-1);
	if (create_float_input_box(engine,
			gui_box->children.data + 1, (t_float_input_box_on_click){0}) < 0)
		return (-1);
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	change_image_color(&gui_box->children.data[0].image, COLOR_SAND);
	change_image_color(&gui_box->children.data[2].image, COLOR_TRANSPARENT);
	(void)type;
	write_centered_string_to_image(&engine->gui.font, &gui_box->children.data[0].image,
		type);
	return (0);
}
