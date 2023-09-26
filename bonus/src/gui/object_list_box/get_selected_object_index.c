/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_selected_object_index.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:37:08 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 17:52:02 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "gui/object_list_box.h"

static size_t	get_light_index(t_engine *engine, t_vector2i click_position,
					int *y);
static size_t	get_object_index(t_engine *engine, t_vector2i click_position,
					int y);

size_t	get_selected_object_index(t_gui_box *self, t_engine *engine,
			t_vector2i click_position)
{
	int		y;
	size_t	result;

	if (click_position.x < OBJECT_LIST_OFFSET
		|| click_position.x >= self->size.y - OBJECT_LIST_OFFSET * 2)
		return (SIZE_MAX);
	y = self->scroll;
	result = get_light_index(engine, click_position, &y);
	if (result != SIZE_MAX)
		return (result);
	y += OBJECT_LIST_SUB_BOX_SIZE / 4;
	result = get_object_index(engine, click_position, y);
	if (result != SIZE_MAX)
		return (result + engine->gui.light_boxes.length);
	return (SIZE_MAX);
}

static size_t	get_light_index(t_engine *engine, t_vector2i click_position,
					int *y)
{
	size_t	i;

	i = engine->gui.light_boxes.length;
	while (i--)
	{
		if (*y <= click_position.y
			&& *y + OBJECT_LIST_SUB_BOX_SIZE >= click_position.y)
			return (i);
		*y += ((t_gui_box *)engine->gui.light_boxes.data)[i].size.y
			+ OBJECT_LIST_OFFSET;
	}
	return (SIZE_MAX);
}

static size_t	get_object_index(t_engine *engine, t_vector2i click_position,
					int y)
{
	size_t	i;

	i = engine->gui.object_boxes.length;
	while (i--)
	{
		if (y <= click_position.y
			&& y + OBJECT_LIST_SUB_BOX_SIZE >= click_position.y)
			return (i);
		y += ((t_gui_box *)engine->gui.object_boxes.data)[i].size.y
			+ OBJECT_LIST_OFFSET;
	}
	return (SIZE_MAX);
}
