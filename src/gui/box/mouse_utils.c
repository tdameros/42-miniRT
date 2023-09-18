/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:57:29 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:21:28 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "gui/box.h"
#include "mlx_wrapper.h"
#include "gui/utils.h"
#include "colors.h"

bool	is_mouse_hovering_box(const t_gui_box *gui_box,
			const t_vector2i box_offset,
			const t_image *image_to_check_for_hover,
			t_vector2i mouse_position)
{
	mouse_position = get_mouse_position_in_box(gui_box, box_offset,
			mouse_position);
	return (mouse_position.x >= 0
		&& mouse_position.x < image_to_check_for_hover->width
		&& mouse_position.y >= 0
		&& mouse_position.y < image_to_check_for_hover->height
		&& get_image_pixel_color(image_to_check_for_hover,
			mouse_position.y, mouse_position.x) != COLOR_TRANSPARENT);
}

t_vector2i	get_mouse_position_in_box(const t_gui_box *self,
				const t_vector2i box_offset, t_vector2i mouse_position)
{
	mouse_position.x -= box_offset.x + self->position.x;
	mouse_position.y -= box_offset.y + self->position.y;
	return (mouse_position);
}
