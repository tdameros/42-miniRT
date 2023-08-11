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

static bool	is_point_in_gui_box(const t_gui_box *gui_box, int *x, int *y);

t_gui_box	*get_clicked_gui_box(t_engine *engine, t_gui_boxes gui_boxes,
				int *x, int *y)
{
	size_t	i;

	i = gui_boxes.size;
	while (i--)
		if (is_point_in_gui_box(gui_boxes.data + i, x, y))
			return (gui_boxes.data + i);
	if (engine == NULL)
		return (NULL);
	if (engine->gui.current_optional_box == SETTINGS_BOX)
		if (is_point_in_gui_box(
				engine->gui.optional_gui_boxes.data + SETTINGS_BOX, x, y))
			return (engine->gui.optional_gui_boxes.data + SETTINGS_BOX);
	return (NULL);
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
