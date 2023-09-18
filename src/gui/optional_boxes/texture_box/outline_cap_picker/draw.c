/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:24:56 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 18:24:57 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "gui/box.h"
#include "mlx_wrapper.h"

void	outline_picker_draw(t_gui_box *self, t_engine *engine,
			t_draw_data draw_data)
{
	if (engine->gui.color_and_material.texture_being_changed == OUTLINE_TEXTURE)
		return (put_image(engine, &self->on_hover_image,
				(t_vector2i){self->position.x + draw_data.offset.x,
				self->position.y + draw_data.offset.y}));
	draw_gui_box_image(self, engine, draw_data);
}

void	cap_picker_draw(t_gui_box *self, t_engine *engine,
			t_draw_data draw_data)
{
	if (engine->gui.color_and_material.texture_being_changed == CAP_TEXTURE)
		return (put_image(engine, &self->on_hover_image,
				(t_vector2i){self->position.x + draw_data.offset.x,
				self->position.y + draw_data.offset.y}));
	draw_gui_box_image(self, engine, draw_data);
}
