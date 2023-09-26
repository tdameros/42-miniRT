/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere_attributes_modification_box.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:31:00 by vfries            #+#    #+#             */
/*   Updated: 2023/08/02 19:32:00 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "gui/box.h"
#include "hooks.h"

static void	add_transformation_boxes(t_engine *engine, t_gui_box *gui_box,
				int *i);
static void	add_reflection_boxes(t_engine *engine, t_gui_box *gui_box, int *i);
static void	add_texture_boxes(t_engine *engine, t_gui_box *gui_box, int *i);

void	init_sphere_attributes_modification_box(t_engine *engine,
			t_gui_box *gui_box)
{
	int	i;

	gui_box->children.size = 8;
	gui_box->children.data = ft_calloc(gui_box->children.size,
			sizeof(*gui_box->children.data));
	if (gui_box->children.data == NULL)
		ft_fatal_error("init_sphere_attributes_modification_box: "
			"malloc failed");
	i = 0;
	add_delete_box(engine, gui_box->children.data + i++, gui_box);
	add_transformation_boxes(engine, gui_box, &i);
	add_reflection_boxes(engine, gui_box, &i);
	add_texture_boxes(engine, gui_box, &i);
}

static void	add_transformation_boxes(t_engine *engine, t_gui_box *gui_box,
				int *i)
{
	int	y;

	y = get_transformations_boxes_index(gui_box);
	add_position_box(engine, gui_box->children.data + (*i)++, &y, gui_box);
	add_radius_box(engine, gui_box->children.data + (*i)++, &y, gui_box);
}

static void	add_reflection_boxes(t_engine *engine, t_gui_box *gui_box, int *i)
{
	int	y;

	y = get_reflections_boxes_index(gui_box);
	add_reflection_box(engine, gui_box->children.data + (*i)++, &y, gui_box);
	add_specular_reflection_box(engine, gui_box->children.data + (*i)++, &y,
		gui_box);
}

static void	add_texture_boxes(t_engine *engine, t_gui_box *gui_box, int *i)
{
	int	y;

	y = get_texture_boxes_index(gui_box);
	add_texture_button(engine, gui_box->children.data + (*i)++, &y, gui_box);
	add_outline_checkerboard_size_box(engine, gui_box->children.data + (*i)++,
		&y, gui_box);
	add_outline_checkerboard_color_toggle_box(engine,
		gui_box->children.data + (*i)++, &y, gui_box);
}
