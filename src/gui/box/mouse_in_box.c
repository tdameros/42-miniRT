/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_in_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:57:29 by vfries            #+#    #+#             */
/*   Updated: 2023/05/03 17:59:33 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "struct/t_gui_box.h"
#include "colors.h"

bool	mouse_is_hovering_box(t_gui_box *self, t_vector2i mouse_position)
{
	return (mouse_position.x >= 0
		&& mouse_position.x < self->size.x
		&& mouse_position.y >= 0
		&& mouse_position.y < self->size.y
		&& get_image_pixel_color(&self->on_hover_image, mouse_position.y,
			mouse_position.x) != COLOR_TRANSPARENT);
}

#if defined __APPLE__

t_vector2i	get_mouse_position(t_gui_box *self, t_minirt *minirt,
								 int x_offset, int y_offset)
{
	t_vector2i	mouse_position;

	mlx_mouse_get_pos(minirt->window.window,
		&mouse_position.x, &mouse_position.y);
	mouse_position.x -= x_offset + self->position.x;
	mouse_position.y -= y_offset + self->position.y;
	return (mouse_position);
}
#elif defined __linux__

t_vector2i	get_mouse_position(t_gui_box *self, t_engine *minirt,
					int x_offset, int y_offset)
{
	t_vector2i	mouse_position;

	mlx_mouse_get_pos(minirt->window.mlx, minirt->window.window,
		&mouse_position.x, &mouse_position.y);
	mouse_position.x -= x_offset + self->position.x;
	mouse_position.y -= y_offset + self->position.y;
	return (mouse_position);
}
#else
# error "Unsuport OS"
#endif //__linux__
