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
					const t_gui_boxes *gui_boxes);
static size_t	get_selected_ppm_box_index(t_gui_box *self, t_engine *engine,
					t_vector2i click_position);

void	textures_and_normal_maps_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	size_t		selected_file_index;
	t_gui_boxes	*gui_boxes;

	if (engine->gui.color_and_material.changing_normal_map_or_texture
		== NORMAL_MAP)
		gui_boxes = &engine->gui.color_and_material.textures_and_normal_maps.\
			normal_maps_boxes;
	else
		gui_boxes = &engine->gui.color_and_material.textures_and_normal_maps.\
			textures_boxes;
	if (gui_boxes->size == 0)
		return ;
	handle_scroll(self, click_data.button, gui_boxes);
	if (click_data.button != BUTTON_LEFT)
		return ;
	selected_file_index = get_selected_ppm_box_index(self, engine,
			click_data.click_position);
	if (selected_file_index == SIZE_MAX)
		return ;
	click_ppm_box(engine, selected_file_index);
}

static void	handle_scroll(t_gui_box *self, const int button,
				const t_gui_boxes *gui_boxes)
{
	int		size_diff_sub_boxes_main_box;

	if (button == SCROLL_UP)
	{
		self->scroll -= 10;
		size_diff_sub_boxes_main_box = self->size.y - \
			((int)gui_boxes->size
				* (gui_boxes->data->size.y + TEXTURE_BOX_PPM_OFFSET));
		if (size_diff_sub_boxes_main_box < 0
			&& self->scroll < size_diff_sub_boxes_main_box)
			self->scroll = size_diff_sub_boxes_main_box;
		else if (size_diff_sub_boxes_main_box >= 0
			&& self->scroll < TEXTURE_BOX_PPM_OFFSET)
			self->scroll = TEXTURE_BOX_PPM_OFFSET;
	}
	if (button != SCROLL_DOWN)
		return ;
	self->scroll += 10;
	if (self->scroll > TEXTURE_BOX_PPM_OFFSET)
		self->scroll = TEXTURE_BOX_PPM_OFFSET;
}

static size_t	get_selected_ppm_box_index(t_gui_box *self, t_engine *engine,
					t_vector2i click_position)
{
	int			y;
	size_t		i;
	t_gui_boxes	*gui_boxes;

	if (engine->gui.color_and_material.changing_normal_map_or_texture
		== NORMAL_MAP)
		gui_boxes = &engine->gui.color_and_material.textures_and_normal_maps.\
			normal_maps_boxes;
	else
		gui_boxes = &engine->gui.color_and_material.textures_and_normal_maps.\
			textures_boxes;
	if (click_position.x < TEXTURE_BOX_PPM_OFFSET
		|| click_position.x >= self->size.y - TEXTURE_BOX_PPM_OFFSET * 2)
		return (SIZE_MAX);
	y = self->scroll;
	i = -1;
	while (++i < gui_boxes->size)
	{
		if (y <= click_position.y
			&& y + gui_boxes->data[i].size.y >= click_position.y)
			return (i);
		y += gui_boxes->data[i].size.y + TEXTURE_BOX_PPM_OFFSET;
	}
	return (SIZE_MAX);
}
