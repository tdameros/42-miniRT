/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_settings_box.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:37:01 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:37:02 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "engine.h"
#include "gui/UI.h"
#include "gui/box.h"
#include "gui/utils.h"
#include "gui/optional_boxes.h"
#include "gui/object_modification_box.h"
#include "hooks.h"

static void	init_children_boxes(t_engine *engine, t_gui_box *gui_box);
static void	add_camera_settings_boxes(t_engine *engine, t_gui_box *gui_box,
				int *y, int *i);
static void	add_performance_settings_boxes(t_engine *engine,
				t_gui_box *gui_box, int *y, int *i);
static void	add_raytracing_settings_boxes(t_engine *engine, t_gui_box *gui_box,
				int *y, int *i);

void	init_settings_box(t_engine *engine, t_gui_box *gui_box,
			const t_gui_box *main_gui_box, const t_gui_box *object_list_box)
{
	*gui_box = create_optional_box(engine, main_gui_box, object_list_box);
	init_children_boxes(engine, gui_box);
}

static void	init_children_boxes(t_engine *engine, t_gui_box *gui_box)
{
	int	i;
	int	y;

	create_n_horizontal_boxes(engine, gui_box, 1, (t_vector2i){
		roundf(gui_box->size.y / 100.f), roundf(gui_box->size.y / 100.f)});
	gui_box = gui_box->children.data;
	gui_box->children.size = 7;
	gui_box->children.data = ft_calloc(gui_box->children.size,
			sizeof(*gui_box->children.data));
	if (gui_box->children.data == NULL)
		ft_fatal_error("Failed to create settings box");
	y = 0;
	i = 0;
	add_camera_settings_boxes(engine, gui_box, &y, &i);
	add_performance_settings_boxes(engine, gui_box, &y, &i);
	add_raytracing_settings_boxes(engine, gui_box, &y, &i);
}

static void	add_camera_settings_boxes(t_engine *engine, t_gui_box *gui_box,
				int *y, int *i)
{
	init_cam_fov_box(engine, gui_box->children.data + (*i)++, y, gui_box);
	init_reset_camera_peaking_box(engine, gui_box->children.data + (*i)++, y,
		gui_box);
	*y += OBJECT_ATTRIBUTE_BOX_CATEGORY_OFFSET_SIZE / get_attribute_box_size()
		* engine->gui.object_attributes_modification_box->size.y;
}

static void	add_performance_settings_boxes(t_engine *engine, t_gui_box *gui_box,
				int *y, int *i)
{
	init_antialiasing_toggle_box(engine, gui_box->children.data + (*i)++, y,
		gui_box);
	init_max_resolution_reduction_box(engine, gui_box->children.data + (*i)++,
		y, gui_box);
	init_min_resolution_reduction_box(engine, gui_box->children.data + (*i)++,
		y, gui_box);
}

static void	add_raytracing_settings_boxes(t_engine *engine, t_gui_box *gui_box,
				int *y, int *i)
{
	init_disable_shadows_box(engine, gui_box->children.data + (*i)++, y,
		gui_box);
	init_bounces_per_pixel_box(engine, gui_box->children.data + (*i)++, y,
		gui_box);
}
