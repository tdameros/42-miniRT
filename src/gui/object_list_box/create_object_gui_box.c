/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object_gui_box.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:53:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/18 15:53:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "engine.h"
#include "gui/box.h"
#include "gui/UI.h"
#include "gui/utils.h"
#include "font/render.h"
#include "gui/object_list_box.h"

static void	init_object_gui_box_children(t_engine *engine, t_gui_box *parent,
				const t_object *object);
static void	init_images(t_engine *engine, t_gui_box *gui_box);
static void	draw_images(t_engine *engine, t_gui_box *parent,
				const t_object *object);

void	create_object_gui_box(t_engine *engine, t_gui_box *gui_box,
			const t_object *object)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){
			engine->gui.object_list_box,
			(t_vector2i){OBJECT_LIST_OFFSET, 0},
			(t_vector2i){engine->gui.object_list_box->size.x \
							- OBJECT_LIST_OFFSET * 2, \
						OBJECT_LIST_SUB_BOX_SIZE},
			true});
	init_object_gui_box_children(engine, gui_box, object);
	init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	change_image_color(&gui_box->on_hover_image, HOVER_GUI_COLOR);
	round_image_corners(&gui_box->on_hover_image, BOX_ROUNDING_RADIUS);
}

static void	init_object_gui_box_children(t_engine *engine, t_gui_box *parent,
				const t_object *object)
{
	create_n_horizontal_boxes(engine, parent, 1,
		(t_boxes_offsets){OBJECT_LIST_OFFSET, OBJECT_LIST_OFFSET}); // TODO check why x offset?
	create_horizontal_boxes(engine, parent->children.data,
		OBJECT_LIST_SUB_BOX_BOXES, 0);
	create_n_horizontal_boxes(engine, parent->children.data->children.data + 2,
		1, (t_boxes_offsets){OBJECT_LIST_OFFSET, OBJECT_LIST_OFFSET});
	init_images(engine, parent->children.data);
	draw_images(engine, parent->children.data, object);
}

static void	init_images(t_engine *engine, t_gui_box *gui_box)
{
	init_image(&gui_box->children.data[0].image, &engine->window, \
		gui_box->children.data[0].size.x, gui_box->children.data[0].size.y);
	init_image(&gui_box->children.data[2].children.data->image, &engine->window,
		gui_box->children.data[2].children.data->size.x,
		gui_box->children.data[2].children.data->size.y);
}

static void	draw_images(t_engine *engine, t_gui_box *parent,
				const t_object *object)
{
	draw_icon(&parent->children.data[0].image, object->type, COLOR_TRANSPARENT,
		object->material);
	change_image_color(&parent->children.data[2].children.data->image,
		COLOR_TRANSPARENT);
	if (object->name != NULL)
		write_centered_string_to_image(&engine->gui.font,
			&parent->children.data[2].children.data->image, object->name);
	else
		write_centered_string_to_image(&engine->gui.font,
			&parent->children.data[2].children.data->image, "(null)");
}
