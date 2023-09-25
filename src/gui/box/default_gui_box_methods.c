/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_gui_box_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:23:22 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:38:17 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_wrapper.h"
#include "gui/box.h"
#include "engine.h"
#include "gui/utils.h"

void	default_gui_box_draw(t_gui_box *self, t_engine *engine,
			t_draw_data draw_data)
{
	size_t	i;

	draw_gui_box_image(self, engine, draw_data);
	i = self->children.size;
	while (i--)
		if (self->children.data[i].draw != NULL)
			self->children.data[i].draw(self->children.data + i, engine,
				(t_draw_data){\
					(t_vector2i){draw_data.offset.x + self->position.x, \
								draw_data.offset.y + self->position.y},
					draw_data.mouse_position});
}

void	draw_gui_box_image(t_gui_box *self, t_engine *engine,
			t_draw_data draw_data)
{
	t_image				*image_to_check_hover_on;
	bool				mouse_is_hovering_box;
	const t_vector2i	position = {self->position.x + draw_data.offset.x,
		self->position.y + draw_data.offset.y};

	if (self->image.data != NULL && self->on_hover_image.data == NULL)
		return (put_image(engine, &self->image, position));
	if (self->on_hover_image.data != NULL)
		image_to_check_hover_on = &self->on_hover_image;
	else
		image_to_check_hover_on = &self->image;
	mouse_is_hovering_box = is_mouse_hovering_box(self, draw_data.offset,
			image_to_check_hover_on, draw_data.mouse_position);
	if (self->on_hover_image.data != NULL && mouse_is_hovering_box)
		return (put_image(engine, &self->on_hover_image, position));
	if (self->image.data != NULL && mouse_is_hovering_box == false)
		put_image(engine, &self->image, position);
}

void	default_gui_box_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	t_gui_box	*clicked_gui_box;

	clicked_gui_box = get_clicked_gui_box(self->children,
			&click_data.click_position.x, &click_data.click_position.y);
	if (clicked_gui_box != NULL && clicked_gui_box->on_click != NULL)
		clicked_gui_box->on_click(clicked_gui_box, engine, click_data);
}
