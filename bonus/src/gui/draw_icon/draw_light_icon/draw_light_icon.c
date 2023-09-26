/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_light_icon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:36:09 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:36:19 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "image.h"
#include "colors.h"
#include "gui/utils.h"

#define BASE_IMAGE_SIZE 1024.f
#define TRANSPARENT_CIRCLE_RADIUS 200.f
#define COLOR_CIRCLE_RADIUS 275.f

void	draw_light_icon(t_image *image,
			const unsigned int background_color, const t_color vec_color)
{
	const float			image_min_size = fminf(image->width, image->height);
	const float			scale = image_min_size / BASE_IMAGE_SIZE;
	const t_vector2f	center = {image->width / 2.f, image->height / 2.f};
	const unsigned int	color = vec_rgb_to_uint(
			vector3f_multiply(vec_color, 255));
	const t_vector2f	offset = {
		.x = image->width / 2.f - image_min_size / 2.f, \
		.y = image->height / 2.f - image_min_size / 2.f};

	change_image_color(image, background_color);
	draw_top_rectangles(image, color, scale, offset);
	draw_bottom_rectangles(image, color, scale, offset);
	draw_side_rectangles(image, color, scale, offset);
	image_draw_circle(image, center, COLOR_CIRCLE_RADIUS * scale, color);
	image_draw_circle(image, center, TRANSPARENT_CIRCLE_RADIUS * scale,
		background_color);
}
