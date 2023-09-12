/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_and_normal_maps_on_click.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:26:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 19:36:51 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "events.h"
#include "gui/optional_boxes.h"

static void		handle_scroll(t_gui_box *self, int button,
					const t_gui_boxes *mesh_boxes);
static size_t	get_selected_mesh_box_index(t_gui_box *self, t_engine *engine,
					t_vector2i click_position);

void	mesh_object_selection_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	size_t		selected_file_index;
	t_gui_boxes	*mesh_boxes;

	mesh_boxes = &engine->gui.mesh_objects.mesh_boxes;
	if (mesh_boxes->size == 0)
		return ;
	handle_scroll(self, click_data.button, mesh_boxes);
	if (click_data.button != BUTTON_LEFT)
		return ;
	selected_file_index = get_selected_mesh_box_index(self, engine,
			click_data.click_position);
	if (selected_file_index == SIZE_MAX)
		return ;
	click_mesh_box(engine, selected_file_index);
}

static void	handle_scroll(t_gui_box *self, const int button,
				const t_gui_boxes *mesh_boxes)
{
	int		size_diff_sub_boxes_main_box;

	if (button == SCROLL_UP)
	{
		self->scroll -= 10;
		size_diff_sub_boxes_main_box = self->size.y - \
			((int)mesh_boxes->size
				* (mesh_boxes->data->size.y + MESH_BOX_OFFSET));
		if (size_diff_sub_boxes_main_box < 0
			&& self->scroll < size_diff_sub_boxes_main_box)
			self->scroll = size_diff_sub_boxes_main_box;
		else if (size_diff_sub_boxes_main_box >= 0
			&& self->scroll < MESH_BOX_OFFSET)
			self->scroll = MESH_BOX_OFFSET;
	}
	if (button != SCROLL_DOWN)
		return ;
	self->scroll += 10;
	if (self->scroll > MESH_BOX_OFFSET)
		self->scroll = MESH_BOX_OFFSET;
}

static size_t	get_selected_mesh_box_index(t_gui_box *self, t_engine *engine,
					t_vector2i click_position)
{
	int			y;
	size_t		i;
	t_gui_boxes	*gui_boxes;

	gui_boxes = &engine->gui.mesh_objects.mesh_boxes;
	if (click_position.x < MESH_BOX_OFFSET
		|| click_position.x >= self->size.y - MESH_BOX_OFFSET * 2)
		return (SIZE_MAX);
	y = self->scroll;
	i = -1;
	while (++i < gui_boxes->size)
	{
		if (y <= click_position.y
			&& y + gui_boxes->data[i].size.y >= click_position.y)
			return (i);
		y += gui_boxes->data[i].size.y + MESH_BOX_OFFSET;
	}
	return (SIZE_MAX);
}
