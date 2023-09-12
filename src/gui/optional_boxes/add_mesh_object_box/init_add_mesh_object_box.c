/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_add_mesh_object_box.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:25:17 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 18:25:18 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "engine.h"
#include "gui/UI.h"
#include "gui/box.h"
#include "gui/utils.h"
#include "gui/optional_boxes.h"

static void	init_children_boxes(t_engine *engine, t_gui_box *gui_box);
static void	init_mesh_object_selection_box(t_engine *engine,
				t_gui_box *gui_box);

void	init_add_mesh_object_box(t_engine *engine, t_gui_box *gui_box,
			const t_gui_box *main_gui_box, const t_gui_box *object_list_box)
{
	*gui_box = create_optional_box(engine, main_gui_box, object_list_box);
	init_children_boxes(engine, gui_box);
}

static void	init_children_boxes(t_engine *engine, t_gui_box *gui_box)
{
	create_vertical_boxes(engine, gui_box, "1 98 1",
		roundf(gui_box->size.y / 100.f));
	init_mesh_object_selection_box(engine, gui_box->children.data + 1);
}

static void	init_mesh_object_selection_box(t_engine *engine,
				t_gui_box *gui_box)
{
	init_image(&gui_box->image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	gui_box->draw = &mesh_object_selection_draw;
	gui_box->on_click = &mesh_object_selection_on_click;
	gui_box->scroll = MESH_BOX_OFFSET;
	engine->gui.mesh_objects.selection_box = gui_box;
	load_mesh_objects(engine);
}
