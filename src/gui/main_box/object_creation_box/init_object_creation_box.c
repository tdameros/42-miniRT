/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_creation_box.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:23:22 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 17:25:13 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "errno.h"

#include "gui/box.h"
#include "gui/main_gui_box.h"
#include "gui/utils.h"
#include "gui/UI.h"
#include "engine.h"
#include "colors.h"

#define NUMBER_OF_OBJECT_TYPES 5

static void	init_object_creation_children(t_engine *engine, t_gui_box *gui_box);
static void	create_images(t_engine *engine, t_gui_box *gui_box);
static void	init_object_creation_box(const t_engine *engine, t_gui_box *gui_box,
				int type);

void	init_object_creation_gui_box(t_engine *minirt, t_gui_box *gui_box,
			t_gui_box *parent)
{
	*gui_box = create_t_gui_box(minirt, (t_gui_box_create){parent,
			(t_vector2i){8, 8},
			(t_vector2i){.y = parent->size.y - 16, \
							.x = parent->size.x / 4 * 3 - 16}, true});
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	init_object_creation_children(minirt, gui_box);
}

static void	init_object_creation_children(t_engine *engine, t_gui_box *gui_box)
{
	create_n_horizontal_boxes(engine, gui_box, NUMBER_OF_OBJECT_TYPES,
		(t_boxes_offsets){ICON_BOX_SEPARATOR, ICON_BOX_SEPARATOR});
	create_images(engine, gui_box);
	init_object_creation_box(engine, gui_box->children.data + 0, SPHERE);
	init_object_creation_box(engine, gui_box->children.data + 1, PLANE);
	init_object_creation_box(engine, gui_box->children.data + 2, CYLINDER);
	init_object_creation_box(engine, gui_box->children.data + 3, CONE);
	init_object_creation_box(engine, gui_box->children.data + 4, LIGHT);
	engine->gui.object_creation_boxes = &gui_box->children;
}

static void	create_images(t_engine *engine, t_gui_box *gui_box)
{
	int	i;

	i = -1;
	while (++i < NUMBER_OF_OBJECT_TYPES)
	{
		init_image(&gui_box->children.data[i].image, &engine->window,
			gui_box->children.data[i].size.x, gui_box->children.data[i].size.y);
		init_image(&gui_box->children.data[i].on_hover_image, &engine->window,
			gui_box->children.data[i].size.x, gui_box->children.data[i].size.y);
	}
}

static void	init_object_creation_box(const t_engine *engine, t_gui_box *gui_box,
				const int type)
{
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	change_image_color(&gui_box->on_hover_image, HOVER_GUI_COLOR);
	draw_icon(&gui_box->image, type, COLOR_TRANSPARENT,
		engine->gui.material_to_assign_to_new_objects);
	draw_icon(&gui_box->on_hover_image, type, HOVER_GUI_COLOR,
		engine->gui.material_to_assign_to_new_objects);
	round_image_corners(&gui_box->on_hover_image, BOX_ROUNDING_RADIUS);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	if (type == SPHERE)
		gui_box->on_click = &sphere_create_on_click;
	else if (type == PLANE)
		gui_box->on_click = &plane_create_on_click;
	else if (type == CYLINDER)
		gui_box->on_click = &cylinder_create_on_click;
	else if (type == CONE)
		gui_box->on_click = &cone_create_on_click;
	else
		gui_box->on_click = &light_create_on_click;
}
