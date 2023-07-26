/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder_attributes_modification_box.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:33:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/01 11:33:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "gui/box.h"
#include "hooks.h"

static int	add_transformation_boxes(t_engine *engine, t_gui_box *gui_box);
static int	add_reflection_boxes(t_engine *engine, t_gui_box *gui_box);
static int	add_texture_boxes(t_engine *engine, t_gui_box *gui_box);

int	init_cylinder_attributes_modification_box(t_engine *engine,
		t_gui_box *gui_box)
{
	gui_box->children.size = 9;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
			* gui_box->children.size);
	if (gui_box->children.data == NULL)
	{
		gui_box->children.size = 0;
		return (-1);
	}
	if (add_transformation_boxes(engine, gui_box) < 0)
		return (-1);
	if (add_reflection_boxes(engine, gui_box) < 0)
		return (-1);
	if (add_texture_boxes(engine, gui_box) < 0)
		return (-1);
	return (0);
}

static int	add_transformation_boxes(t_engine *engine, t_gui_box *gui_box)
{
	int	y;

	y = get_transformations_boxes_index(gui_box);
	if (add_position_box(engine, gui_box->children.data, &y, gui_box) < 0)
	{
		gui_box->children.size = 0;
		free(gui_box->children.data);
		gui_box->children.data = NULL;
		return (-1);
	}
	if (add_normal_box(engine, gui_box->children.data + 1, &y, gui_box) < 0)
	{
		gui_box->children.size = 1;
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	if (add_radius_box(engine, gui_box->children.data + 2, &y, gui_box) < 0)
	{
		gui_box->children.size = 2;
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	if (add_height_box(engine, gui_box->children.data + 3, &y, gui_box) < 0)
	{
		gui_box->children.size = 3;
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	return (0);
}

static int	add_reflection_boxes(t_engine *engine, t_gui_box *gui_box)
{
	int	y;

	y = get_reflections_boxes_index(gui_box);
	if (add_reflection_box(engine, gui_box->children.data + 4, &y, gui_box) < 0)
	{
		gui_box->children.size = 4;
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	if (add_specular_reflection_box(engine, gui_box->children.data + 5, &y,
			gui_box) < 0)
	{
		gui_box->children.size = 5;
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	return (0);
}

static int	add_texture_boxes(t_engine *engine, t_gui_box *gui_box)
{
	int	y;

	y = get_texture_boxes_index(gui_box);
	if (add_checkered_pattern_color_toggle_box(engine,
			gui_box->children.data + 6, &y, gui_box) < 0)
	{
		gui_box->children.size = 6;
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	if (add_outline_checkerboard_size_box(engine, gui_box->children.data + 7,
			&y, gui_box) < 0)
	{
		gui_box->children.size = 7;
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	if (add_cap_checkerboard_size_box(engine, gui_box->children.data + 8,
			&y, gui_box) < 0)
	{
		gui_box->children.size = 8;
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	return (0);
}
