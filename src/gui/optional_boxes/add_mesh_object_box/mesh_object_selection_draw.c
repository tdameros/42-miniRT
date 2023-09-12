/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_object_selection_draw.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:11:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 18:25:23 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "engine.h"
#include "gui/box.h"
#include "gui/optional_boxes.h"
#include "gui/utils.h"

static void	draw_mesh_boxes(t_engine *engine, int y, t_draw_data draw_data);
static void	draw_mesh_box(t_gui_box *self, t_vector2i offset,
				t_draw_data draw_data);

void	mesh_object_selection_draw(t_gui_box *self, t_engine *engine,
			const t_draw_data draw_data)
{
	reload_mesh_objects(engine);
	change_image_color(&self->image, COLOR_TRANSPARENT);
	draw_mesh_boxes(engine, self->scroll, (t_draw_data){\
		(t_vector2i){draw_data.offset.x + self->position.x, \
					draw_data.offset.y + self->position.y},
		draw_data.mouse_position});
	mlx_put_image_to_window(engine->window.mlx, engine->window.window,
		self->image.data, self->position.x + draw_data.offset.x,
		self->position.y + draw_data.offset.y);
	// TODO make a linux version of the function
}

static void	draw_mesh_boxes(t_engine *engine, int y,
				const t_draw_data draw_data)
{
	size_t		i;
	t_gui_boxes	*gui_boxes;

	gui_boxes = &engine->gui.mesh_objects.mesh_boxes;
	i = -1;
	while (++i < gui_boxes->size)
	{
		draw_mesh_box(gui_boxes->data + i, (t_vector2i){0, y},
			(t_draw_data){\
				(t_vector2i){draw_data.offset.x, draw_data.offset.y + y}, \
				draw_data.mouse_position});
		y += gui_boxes->data[i].size.y + MESH_BOX_OFFSET;
	}
}

static void	draw_mesh_box(t_gui_box *self, const t_vector2i offset,
				const t_draw_data draw_data)
{
	if (is_mouse_hovering_box(self, draw_data.offset, &self->image,
			draw_data.mouse_position))
		put_image_to_image(&self->parent->image, &self->on_hover_image,
			(t_vector2i){self->position.x + offset.x, \
			self->position.y + offset.y});
	else
		put_image_to_image(&self->parent->image, &self->image,
			(t_vector2i){self->position.x + offset.x, \
			self->position.y + offset.y});
}
