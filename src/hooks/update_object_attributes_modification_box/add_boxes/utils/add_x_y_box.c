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

static void	init_x_y_box_children(t_engine *engine, t_gui_box *gui_box);
static void	init_x_y_buttons_children(t_engine *engine, t_gui_box *gui_box);
static void	create_x_y_input_box(t_engine *engine, t_gui_box *gui_box,
				const char *type);

void	add_x_y_box(t_engine *engine, t_gui_box *gui_box, int *i,
			t_gui_box *parent)
{
	const t_vector2i	position = {.x = 0, .y = *i};
	const t_vector2i	size = {.x = parent->size.x, \
								.y = get_xyz_box_size(parent)};

	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent, position,
			size, true});
	*i += gui_box->size.y + OBJECT_ATTRIBUTE_BOX_OFFSET;
	init_x_y_box_children(engine, gui_box);
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
}

static void	init_x_y_box_children(t_engine *engine, t_gui_box *gui_box)
{
	create_vertical_boxes(engine, gui_box, "40 60", 0);
	init_x_y_buttons_children(engine, gui_box->children.data + 1);
	init_image(&gui_box->children.data[0].image, &engine->window,
		gui_box->children.data[0].size.x, gui_box->children.data[0].size.y);
	change_image_color(&gui_box->children.data[0].image, COLOR_TRANSPARENT);
}

static void	init_x_y_buttons_children(t_engine *engine, t_gui_box *gui_box)
{
	create_n_horizontal_boxes(engine, gui_box, 2, (t_boxes_offsets){4, 0});
	create_x_y_input_box(engine, gui_box->children.data + 0, "x");
	create_x_y_input_box(engine, gui_box->children.data + 1, "y");
}

static void	create_x_y_input_box(t_engine *engine, t_gui_box *gui_box,
				const char *type)
{
	create_vertical_boxes(engine, gui_box, "40 55 5", 0);
	create_float_input_box(engine, gui_box->children.data + 1,
		(t_float_input_box_on_click){0});
	init_description_box(engine, gui_box->children.data, type);
}
