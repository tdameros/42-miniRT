/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:25:11 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 19:47:10 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_wrapper.h"
#include "gui/box.h"

void	texture_picker_draw(t_gui_box *self, t_engine *engine,
			t_draw_data draw_data)
{
	if (engine->gui.color_and_material.changing_normal_map_or_texture
		== TEXTURE)
		return (put_image(engine, &self->on_hover_image,
				(t_vector2i){self->position.x + draw_data.offset.x,
				self->position.y + draw_data.offset.y}));
	draw_gui_box_image(self, engine, draw_data);
}

void	normal_map_picker_draw(t_gui_box *self, t_engine *engine,
			t_draw_data draw_data)
{
	if (engine->gui.color_and_material.changing_normal_map_or_texture
		== NORMAL_MAP)
		return (put_image(engine, &self->on_hover_image,
				(t_vector2i){self->position.x + draw_data.offset.x,
				self->position.y + draw_data.offset.y}));
	draw_gui_box_image(self, engine, draw_data);
}
