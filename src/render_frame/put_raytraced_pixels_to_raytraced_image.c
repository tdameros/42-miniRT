/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_raytraced_pixels_to_raytraced_image.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 04:03:01 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 04:08:49 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "engine.h"

void	put_raytraced_pixels_to_raytraced_image(t_engine *engine)
{
	unsigned int		*image_cursor;
	const unsigned int	*image_cursor_limit = engine->ray_traced_image.address
		+ engine->ray_traced_image.size;
	t_color				*ray_traced_pixel_cursor;

	image_cursor = engine->ray_traced_image.address;
	ray_traced_pixel_cursor = engine->raytraced_pixels.data;
	while (image_cursor < image_cursor_limit)
		*image_cursor++ = vec_rgb_to_uint(*ray_traced_pixel_cursor++);
}
