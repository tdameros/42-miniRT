/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list_gui_box_draw.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:11:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:22:11 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "engine.h"
#include "gui/UI.h"
#include "gui/box.h"
#include "gui/object_list_box.h"
#include "gui/utils.h"

static void	draw_light_boxes(t_engine *engine, int *y, t_draw_data draw_data);
static void	draw_object_boxes(t_engine *engine, int y, t_draw_data draw_data);
static void	draw_object_and_light_gui_box(t_gui_box *self, t_engine *engine,
				int y, t_draw_data draw_data);
void		draw_object_and_light_gui_box_children(t_gui_box *gui_box,
				t_engine *engine, t_vector2i offset);

void	object_list_gui_box_draw(t_gui_box *self, t_engine *engine,
			t_draw_data draw_data)
{
	const t_vector2i	box_offset = get_left_box_decal(engine,
			&engine->gui.gui_boxes.data[1]);
	int					y;

	put_image_to_image(&self->image, &engine->ray_traced_image,
		(t_vector2i){-self->position.x - box_offset.x, \
					-self->position.y - box_offset.y});
	add_color_to_image(&self->image, BASE_GUI_COLOR);
	round_image_corners(&self->image, BOX_ROUNDING_RADIUS);
	y = self->scroll;
	draw_light_boxes(engine, &y, (t_draw_data){\
		(t_vector2i){draw_data.offset.x + self->position.x, \
					draw_data.offset.y + self->position.y},
		draw_data.mouse_position});
	y += (engine->gui.light_boxes.length > 0) * (OBJECT_LIST_SUB_BOX_SIZE / 4);
	draw_object_boxes(engine, y, (t_draw_data){\
		(t_vector2i){draw_data.offset.x + self->position.x, \
					draw_data.offset.y + self->position.y},
		draw_data.mouse_position});
	mlx_put_image_to_window(engine->window.mlx, engine->window.window,
		self->image.data, self->position.x + draw_data.offset.x,
		self->position.y + draw_data.offset.y);
	// TODO make a linux version of the function
}

static void	draw_light_boxes(t_engine *engine, int *y, t_draw_data draw_data)
{
	size_t	i;

	i = engine->gui.light_boxes.length;
	while (i--)
	{
		draw_object_and_light_gui_box(
			&((t_gui_box *)engine->gui.light_boxes.data)[i], engine, *y,
			(t_draw_data){\
				(t_vector2i){draw_data.offset.x, draw_data.offset.y + *y}, \
				draw_data.mouse_position});
		*y += ((t_gui_box *)engine->gui.light_boxes.data)[i].size.y
			+ OBJECT_LIST_OFFSET;
	}
}

static void	draw_object_boxes(t_engine *engine, int y, t_draw_data draw_data)
{
	size_t	i;

	i = engine->gui.object_boxes.length;
	while (i--)
	{
		draw_object_and_light_gui_box(
			&((t_gui_box *)engine->gui.object_boxes.data)[i], engine, y,
			(t_draw_data){\
				(t_vector2i){draw_data.offset.x, draw_data.offset.y + y}, \
				draw_data.mouse_position});
		y += ((t_gui_box *)engine->gui.object_boxes.data)[i].size.y
			+ OBJECT_LIST_OFFSET;
	}
}

static void	draw_object_and_light_gui_box(t_gui_box *self, t_engine *engine,
			int y, t_draw_data draw_data)
{
	size_t	i;

	if (is_mouse_hovering_box(self, draw_data.offset, &self->image,
			draw_data.mouse_position)
		&& is_mouse_hovering_box(self->parent,
			get_box_offset(self->parent), \
			&self->parent->image, draw_data.mouse_position))
		put_image_to_image(&engine->gui.object_list_box->image,
			&self->on_hover_image,
			(t_vector2i){self->position.x, self->position.y + y});
	else
		put_image_to_image(&engine->gui.object_list_box->image,
			&self->image,
			(t_vector2i){self->position.x, self->position.y + y});
	i = self->children.size;
	while (i--)
		draw_object_and_light_gui_box_children(self->children.data + i, engine,
			(t_vector2i){self->position.x, self->position.y + y});
	// TODO Make a custom version of put_image_to_image() to not change the
	// color if == COLOR_TRANSPARENT since it currently writes over the rounded
	// edges
}

void	draw_object_and_light_gui_box_children(t_gui_box *gui_box,
			t_engine *engine, t_vector2i offset)
{
	size_t	i;

	if (gui_box->image.data != NULL)
		put_image_to_image(&engine->gui.object_list_box->image,
			&gui_box->image,
			(t_vector2i){gui_box->position.x + offset.x, \
						gui_box->position.y + offset.y});
	i = gui_box->children.size;
	while (i--)
		draw_object_and_light_gui_box_children(gui_box->children.data + i,
			engine,
			(t_vector2i){gui_box->position.x + offset.x, \
						gui_box->position.y + offset.y});
}
