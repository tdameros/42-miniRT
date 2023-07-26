/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_x_y_box.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:55:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/23 18:55:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "engine.h"
#include "gui/box.h"
#include "hooks.h"
#include "gui/object_modification_box.h"
#include "gui/UI.h"
#include "font/render.h"
#include "gui/utils.h"

static int	init_x_y_box_children(t_engine *engine, t_gui_box *gui_box);
static int	add_x_y_buttons(t_engine *engine, t_gui_box *gui_box);
static int	init_x_y_buttons_children(t_engine *engine, t_gui_box *gui_box);
static int	create_x_y_input_box(t_engine *engine, t_gui_box *gui_box,
				const char *type);

int	add_x_y_box(t_engine *engine, t_gui_box *gui_box, int *i,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent, \
		(t_vector2i){
			.x = 0,
			.y = *i}, \
		(t_vector2i){
			.x = parent->size.x,
			.y = get_xyz_box_size(parent)}, \
		true});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	*i += gui_box->size.y + OBJECT_ATTRIBUTE_BOX_OFFSET;
	if (init_x_y_box_children(engine, gui_box) < 0)
	{
		destroy_t_image(&engine->window, &gui_box->image);
		ft_bzero(gui_box, sizeof(*gui_box));
		return (-1);
	}
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	return (0);
}

static int	init_x_y_box_children(t_engine *engine, t_gui_box *gui_box)
{
	// TODO leaks
	if (create_vertical_boxes(engine, gui_box, "40 60", 0) < 0)
		return (-1);
	if (add_x_y_buttons(engine, gui_box->children.data + 1) < 0)
		return (-1);
	if (init_image(&gui_box->children.data[0].image, &engine->window,
			gui_box->children.data[0].size.x, gui_box->children.data[0].size.y)
		< 0)
		return (-1);
	change_image_color(&gui_box->children.data[0].image, COLOR_TRANSPARENT);
	return (0);
}

static int	add_x_y_buttons(t_engine *engine, t_gui_box *gui_box)
{
	if (init_x_y_buttons_children(engine, gui_box) < 0)
	{
		destroy_t_image(&engine->window, &gui_box->image);
		ft_bzero(gui_box, sizeof(*gui_box));
		return (-1);
	}
	return (0);
}

static int	init_x_y_buttons_children(t_engine *engine, t_gui_box *gui_box)
{
	// TODO leaks
	if (create_n_horizontal_boxes(engine, gui_box, 2,
			(t_boxes_offsets){4, 0}) < 0)
		return (ft_print_error("create n horizontal box failed"), -1);
	if (create_x_y_input_box(engine, gui_box->children.data + 0, "x") < 0)
		return (-1);
	if (create_x_y_input_box(engine, gui_box->children.data + 1, "y") < 0)
		return (-1);
	return (0);
}

static int	create_x_y_input_box(t_engine *engine, t_gui_box *gui_box,
				const char *type)
{
	// TODO leaks
	if (create_vertical_boxes(engine, gui_box, "40 55 5", 0) < 0)
		return (-1);
	if (create_float_input_box(engine,
			gui_box->children.data + 1, (t_float_input_box_on_click){0}) < 0)
		return (-1);
	if (init_description_box(engine, gui_box->children.data, type) < 0)
		return (-1);
	return (0);
}
