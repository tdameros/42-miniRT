/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_plus_minus_box.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:48:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:37:33 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"
#include "gui/UI.h"
#include "gui/utils.h"
#include "gui/object_modification_box.h"
#include "gui/optional_boxes.h"
#include "hooks.h"

static void	init_plus_minus_box_children(t_engine *engine, t_gui_box *gui_box);

void	add_plus_minus_box(t_engine *engine, t_gui_box *gui_box, int *y,
			t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent, \
		(t_vector2i){\
				.x = 0, \
				.y = *y}, \
		(t_vector2i){\
				.x = parent->size.x, \
				.y = get_normal_box_size(\
					engine->gui.object_attributes_modification_box)}, \
		true});
	*y += gui_box->size.y + OBJECT_ATTRIBUTE_BOX_OFFSET;
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	init_plus_minus_box_children(engine, gui_box);
}

static void	init_plus_minus_box_children(t_engine *engine, t_gui_box *gui_box)
{
	const t_float_input_box_on_click	on_click = {
		.plus = NULL,
		.text_box = NULL,
		.minus = NULL};

	create_horizontal_boxes(engine, gui_box, "65 35", 0);
	init_image(&gui_box->children.data[0].image, &engine->window,
		gui_box->children.data[0].size.x, gui_box->children.data[0].size.y);
	change_image_color(&gui_box->children.data[0].image, COLOR_TRANSPARENT);
	create_float_input_box(engine, gui_box->children.data + 1, on_click);
}
