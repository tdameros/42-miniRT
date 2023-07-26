/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_icons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:56:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/12 13:56:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "gui/UI.h"
#include "gui/utils.h"
#include "gui/object_list_box.h"

static void	update_object_list_icon(t_engine *engine, t_material material);
static void	redraw_object_creation_box(t_gui_box *gui_box, int type,
				t_material material);

void	redraw_icons(t_engine *engine, t_material material)
{
	update_object_list_icon(engine, material);
	engine->gui.material_to_assign_to_new_objects = material;
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 0,
		SPHERE, material);
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 1,
		PLANE, material);
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 2,
		CYLINDER, material);
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 3,
		CONE, material);
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 4,
		LIGHT, material);
}

static void	update_object_list_icon(t_engine *engine, t_material material)
{
	size_t		index;
	t_gui_box	*object_box;

	if (engine->gui.selected_object.object != NULL)
	{
		index = engine->gui.selected_object.object - engine->scene.objects.data;
		object_box = (t_gui_box *)engine->gui.object_boxes.data + index;
		draw_icon(object_box_get_icon_image(object_box),
			engine->gui.selected_object.object->type, COLOR_TRANSPARENT,
			material);
	}
	else if (engine->gui.selected_object.light != NULL)
	{
		index = engine->gui.selected_object.light - engine->scene.lights.data;
		object_box = (t_gui_box *)engine->gui.light_boxes.data + index;
		draw_icon(object_box_get_icon_image(object_box), LIGHT,
			COLOR_TRANSPARENT, material);
	}
}

static void	redraw_object_creation_box(t_gui_box *gui_box,
				const int type, const t_material material)
{
	draw_icon(&gui_box->image, type, COLOR_TRANSPARENT, material);
	draw_icon(&gui_box->on_hover_image, type, HOVER_GUI_COLOR, material);
	round_image_corners(&gui_box->on_hover_image, BOX_ROUNDING_RADIUS);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
}
