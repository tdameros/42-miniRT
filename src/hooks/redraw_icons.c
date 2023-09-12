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

static void	redraw_icons_from_light(t_engine *engine, const t_light *light);
static void	redraw_icons_from_object(t_engine *engine,
				const t_object *base_object);
static void	update_object_list_icon(t_engine *engine);
static void	redraw_object_creation_box(t_gui_box *gui_box,
				const t_object *object, const t_light *light);

void	redraw_icons(t_engine *engine, const t_object *object,
			const t_light *light)
{
	if (light != NULL)
		redraw_icons_from_light(engine, light);
	else if (object != NULL)
		redraw_icons_from_object(engine, object);
	else
		return ;
	update_object_list_icon(engine);
}

static void	redraw_icons_from_light(t_engine *engine, const t_light *light)
{
	t_object	object;

	material_free(
		&engine->gui.color_and_material.material_to_assign_to_new_objects);
	object.material = material_create(light->color, 0, 0);
	engine->gui.color_and_material.material_to_assign_to_new_objects
		= object.material;
	object.type = SPHERE;
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 0,
		&object, NULL);
	object.type = PLANE;
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 1,
		&object, NULL);
	object.type = CYLINDER;
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 2,
		&object, NULL);
	object.type = CONE;
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 3,
		&object, NULL);
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 5,
		NULL, light);
}

static void	redraw_icons_from_object(t_engine *engine,
				const t_object *base_object)
{
	t_object	object;
	t_light		light;

	material_deep_copy(
		&engine->gui.color_and_material.material_to_assign_to_new_objects,
		&base_object->material);
	object = *base_object;
	object.type = SPHERE;
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 0,
		&object, NULL);
	object.type = PLANE;
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 1,
		&object, NULL);
	object.type = CYLINDER;
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 2,
		&object, NULL);
	object.type = CONE;
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 3,
		&object, NULL);
	light.color = base_object->material.albedo;
	redraw_object_creation_box(engine->gui.object_creation_boxes->data + 5,
		NULL, &light);
}

static void	update_object_list_icon(t_engine *engine)
{
	size_t		index;
	t_object	*object;
	t_light		*light;
	t_gui_box	*object_box;

	object = engine->gui.selected_object.object;
	light = engine->gui.selected_object.light;
	if (object != NULL)
	{
		index = object - engine->scene.objects.data;
		object_box = (t_gui_box *)engine->gui.object_boxes.data + index;
		draw_icon(object_box_get_icon_image(object_box), object, NULL,
			COLOR_TRANSPARENT);
	}
	else if (light != NULL)
	{
		index = light - engine->scene.lights.data;
		object_box = (t_gui_box *)engine->gui.light_boxes.data + index;
		draw_icon(object_box_get_icon_image(object_box), NULL, light,
			COLOR_TRANSPARENT);
	}
}

static void	redraw_object_creation_box(t_gui_box *gui_box,
				const t_object *object, const t_light *light)
{
	draw_icon(&gui_box->image, object, light, COLOR_TRANSPARENT);
	draw_icon(&gui_box->on_hover_image, object, light, HOVER_GUI_COLOR);
	round_image_corners(&gui_box->on_hover_image, BOX_ROUNDING_RADIUS);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
}
