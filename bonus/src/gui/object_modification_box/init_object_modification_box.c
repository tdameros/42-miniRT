/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_modification_box.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:25:07 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:25:07 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "gui/box.h"
#include "colors.h"
#include "gui/object_modification_box.h"
#include "gui/utils.h"
#include "gui/UI.h"

static void	init_object_modification_gui_box_children(t_engine *engine,
				t_gui_box *parent);

void	init_object_modification_gui_box(t_engine *engine, t_gui_box *gui_box,
			const t_gui_box *main_gui_box)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){NULL, \
			(t_vector2i){\
				.x = engine->window.size.x - engine->window.size.x / 4 \
					- main_gui_box->position.x, \
				.y = main_gui_box->size.y \
					+ main_gui_box->position.y * 2}, \
			(t_vector2i){\
				.x = engine->window.size.x / 4, \
				.y = engine->window.size.y \
					- (main_gui_box->size.y + main_gui_box->position.y * 3)}, \
			true});
	change_image_color(&gui_box->image, BASE_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	init_object_modification_gui_box_children(engine, gui_box);
}

static void	init_object_modification_gui_box_children(t_engine *engine,
				t_gui_box *parent)
{
	create_vertical_boxes(engine, parent, "1 82 1 15 1",
		roundf(parent->size.y / 100.f));
	engine->gui.object_attributes_modification_box = parent->children.data + 1;
	init_rgb_picker(engine, parent->children.data + 3);
	parent->children.data[0].draw = NULL;
	parent->children.data[0].on_click = NULL;
	parent->children.data[2].draw = NULL;
	parent->children.data[2].on_click = NULL;
	parent->children.data[4].draw = NULL;
	parent->children.data[4].on_click = NULL;
}
