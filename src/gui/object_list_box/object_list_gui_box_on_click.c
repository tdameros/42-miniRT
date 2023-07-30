/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list_gui_box_on_click.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:26:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 17:45:32 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "events.h"
#include "gui/object_list_box.h"
#include "hooks.h"

static bool		handle_scroll(t_gui_box *self, t_engine *engine, int button);
static void		select_light(t_engine *engine, size_t index);
static void		select_object(t_engine *engine, size_t index);

void	object_list_gui_box_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	size_t	selected_object_index;

	if (handle_scroll(self, engine, click_data.button))
		return ;
	if (click_data.button != BUTTON_LEFT)
		return ;
	selected_object_index = get_selected_object_index(self, engine,
			click_data.click_position);
	if (selected_object_index == SIZE_MAX)
		return ;
	if (selected_object_index < engine->gui.light_boxes.length)
		select_light(engine, selected_object_index);
	else
		select_object(engine, selected_object_index
			- engine->gui.light_boxes.length);
}

static bool	handle_scroll(t_gui_box *self, t_engine *engine, const int button)
{
	int		size_diff_sub_boxes_main_box;

	if (button == SCROLL_UP)
	{
		self->scroll -= 10;
		size_diff_sub_boxes_main_box = self->size.y - \
			((int)(engine->gui.light_boxes.length
					+ engine->gui.object_boxes.length)
				* (OBJECT_LIST_SUB_BOX_SIZE + OBJECT_LIST_OFFSET)
				+ OBJECT_LIST_OFFSET + OBJECT_LIST_SUB_BOX_SIZE / 4);
		if (size_diff_sub_boxes_main_box < 0
			&& self->scroll < size_diff_sub_boxes_main_box)
			self->scroll = size_diff_sub_boxes_main_box;
		else if (size_diff_sub_boxes_main_box >= 0
			&& self->scroll < OBJECT_LIST_OFFSET)
			self->scroll = OBJECT_LIST_OFFSET;
		return (true);
	}
	if (button != SCROLL_DOWN)
		return (false);
	self->scroll += 10;
	if (self->scroll > OBJECT_LIST_OFFSET)
		self->scroll = OBJECT_LIST_OFFSET;
	return (true);
}

static void	select_light(t_engine *engine, size_t index)
{
	t_material	material;

	if (index >= engine->scene.lights.length)
		return ;
	engine->gui.selected_object.light = engine->scene.lights.data + index;
	engine->gui.selected_object.object = NULL;
	update_color_picker_color(&engine->gui);
	material = material_create(engine->gui.selected_object.light->color, 0, 0);
	redraw_icons(engine, material);
	update_object_attributes_modification_box(engine);
}

static void	select_object(t_engine *engine, size_t index)
{
	if (index >= engine->scene.objects.length)
		return ;
	engine->gui.selected_object.object = engine->scene.objects.data + index;
	engine->gui.selected_object.light = NULL;
	update_color_picker_color(&engine->gui);
	redraw_icons(engine, engine->gui.selected_object.object->material);
	update_object_attributes_modification_box(engine);
}
