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

static int	init_object_gui_box_children(t_engine *engine, t_gui_box *parent,
				const t_object *object);
static int	init_images(t_engine *engine, t_gui_box *gui_box);
static void	draw_images(t_engine *engine, t_gui_box *parent,
				const t_object *object);

int	create_object_gui_box(t_engine *engine, t_gui_box *gui_box,
		const t_object *object)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){
			engine->gui.object_list_box,
			(t_vector2i){OBJECT_LIST_OFFSET, 0},
			(t_vector2i){engine->gui.object_list_box->size.x \
							- OBJECT_LIST_OFFSET * 2, \
						OBJECT_LIST_SUB_BOX_SIZE},
			true});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	if (init_object_gui_box_children(engine, gui_box, object) < 0)
		return (-1); // TODO free image
	gui_box->draw = &object_and_light_gui_box_draw;
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	return (0);
}

static int	init_object_gui_box_children(t_engine *engine, t_gui_box *parent,
				const t_object *object)
{
	if (create_n_horizontal_boxes(engine, parent, 1,
			(t_boxes_offsets){OBJECT_LIST_OFFSET, OBJECT_LIST_OFFSET}) < 0)
		return (-1);
	if (create_horizontal_boxes(engine, parent->children.data,
			OBJECT_LIST_SUB_BOX_BOXES, 0) < 0)
	{
		free(parent->children.data);
		ft_bzero(&parent->children, sizeof(parent->children));
		return (-1);
	}
	if (init_images(engine, parent->children.data) < 0)
	{
		free(parent->children.data->children.data);
		ft_bzero(&parent->children.data->children,
			sizeof(parent->children.data->children));
		free(parent->children.data);
		ft_bzero(&parent->children, sizeof(parent->children));
		return (-1);
	}
	parent->children.data->draw = &object_and_light_gui_box_draw;
	parent->children.data->children.data[0].draw
		= &object_and_light_gui_box_draw;
	parent->children.data->children.data[2].draw
		= &object_and_light_gui_box_draw;
	draw_images(engine, parent->children.data, object);
	return (0);
}

static int	init_images(t_engine *engine, t_gui_box *gui_box)
{
	if (init_image(&gui_box->children.data[0].image, &engine->window, \
		gui_box->children.data[0].size.x, gui_box->children.data[0].size.y) < 0)
		return (-1);
	if (init_image(&gui_box->children.data[2].image, &engine->window, \
		gui_box->children.data[2].size.x, gui_box->children.data[2].size.y) < 0)
	{
		// TODO free previous image
		return (-1);
	}
	return (0);
}

static void	draw_images(t_engine *engine, t_gui_box *parent,
				const t_object *object)
{
	draw_icon(&parent->children.data[0].image, object->type, COLOR_TRANSPARENT,
		object->material);
	change_image_color(&parent->children.data[2].image, COLOR_TRANSPARENT);
	if (object->name != NULL)
		write_centered_string_to_image(&engine->gui.font,
			&parent->children.data[2].image, object->name);
	else
		write_centered_string_to_image(&engine->gui.font,
			&parent->children.data[2].image, "(null)");
}
