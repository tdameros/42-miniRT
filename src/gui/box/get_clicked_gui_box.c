/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clicked_gui_box.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:22:32 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:22:43 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "gui/box.h"
#include "gui/utils.h"

static bool	is_point_in_root_gui_box(const t_gui_box *gui_box, int *x, int *y,
				t_vector2i offset);
static bool	is_point_in_gui_box(const t_gui_box *gui_box, int *x, int *y);

t_gui_box	*get_clicked_root_gui_box(t_engine *engine, int *x, int *y)
{
	int			i;

	if (is_point_in_root_gui_box(&engine->gui.gui_boxes.data[0], x, y,
			get_top_box_decal(engine, &engine->gui.gui_boxes.data[0])))
		return (&engine->gui.gui_boxes.data[0]);
	if (is_point_in_root_gui_box(&engine->gui.gui_boxes.data[1], x, y,
			get_right_box_decal(engine, &engine->gui.gui_boxes.data[1])))
		return (&engine->gui.gui_boxes.data[1]);
	if (is_point_in_root_gui_box(&engine->gui.gui_boxes.data[2], x, y,
			get_left_box_decal(engine, &engine->gui.gui_boxes.data[1])))
		return (&engine->gui.gui_boxes.data[2]);
	if (engine->gui.current_optional_box != NO_OPTIONAL_BOX)
	{
		i = engine->gui.current_optional_box;
		if (is_point_in_root_gui_box(
				engine->gui.optional_gui_boxes.data + i, x, y,
				get_left_box_decal(engine, &engine->gui.gui_boxes.data[1])))
			return (engine->gui.optional_gui_boxes.data + i);
	}
	return (NULL);
}

t_gui_box	*get_clicked_gui_box(t_gui_boxes gui_boxes, int *x, int *y)
{
	size_t	i;

	i = gui_boxes.size;
	while (i--)
		if (is_point_in_gui_box(gui_boxes.data + i, x, y))
			return (gui_boxes.data + i);
	return (NULL);
}

static bool	is_point_in_root_gui_box(const t_gui_box *gui_box, int *x, int *y,
				const t_vector2i offset)
{
	const t_vector2i	position = {gui_box->position.x + offset.x, \
									gui_box->position.y + offset.y};

	if (*x >= position.x
		&& *x < position.x + gui_box->size.x
		&& *y >= position.y
		&& *y < position.y + gui_box->size.y)
	{
		*x -= position.x;
		*y -= position.y;
		return (true);
	}
	return (false);
}


static bool	is_point_in_gui_box(const t_gui_box *gui_box, int *x, int *y)
{
	if (*x >= gui_box->position.x
		&& *x < gui_box->position.x + gui_box->size.x
		&& *y >= gui_box->position.y
		&& *y < gui_box->position.y + gui_box->size.y)
	{
		*x -= gui_box->position.x;
		*y -= gui_box->position.y;
		return (true);
	}
	return (false);
}
