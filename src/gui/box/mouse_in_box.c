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

#include "gui/box.h"
#include "colors.h"

bool	mouse_is_hovering_box(const t_image *image_to_check_for_hover,
			t_vector2i mouse_position)
{
	return (mouse_position.x >= 0
		&& mouse_position.x < image_to_check_for_hover->width
		&& mouse_position.y >= 0
		&& mouse_position.y < image_to_check_for_hover->height
		&& get_image_pixel_color(image_to_check_for_hover, mouse_position.y,
			mouse_position.x) != COLOR_TRANSPARENT);
}

#if defined __APPLE__

t_vector2i	get_mouse_position(t_gui_box *self, t_engine *engine,
				int x_offset, int y_offset)
{
	t_vector2i	mouse_position;

	mlx_mouse_get_pos(engine->window.window,
		&mouse_position.x, &mouse_position.y);
	mouse_position.x -= x_offset + self->position.x;
	mouse_position.y -= y_offset + self->position.y;
	return (mouse_position);
}
#elif defined __linux__

t_vector2i	get_mouse_position(t_gui_box *self, t_engine *engine,
					int x_offset, int y_offset)
{
	t_vector2i	mouse_position;

	mlx_mouse_get_pos(engine->window.mlx, engine->window.window,
		&mouse_position.x, &mouse_position.y);
	mouse_position.x -= x_offset + self->position.x;
	mouse_position.y -= y_offset + self->position.y;
	return (mouse_position);
}
#else
# error "Unsuport OS"
#endif //__linux__
