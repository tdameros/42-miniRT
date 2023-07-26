/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_check_mark.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:44:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/21 01:44:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "font/render.h"

void	image_draw_check_mark(t_image *image, const unsigned int color,
			const float border)
{
	const t_vector2f			points[] = {\
		{0.225f, 5.24f}, \
		{4.395f, 9.09f}, \
		{9.775f, 3.26f}, \
		{8.795f, 2.35f}, \
		{4.295f, 7.22f}, \
		{1.105f, 4.28f}
	};
	t_glyph_generated_points	draw_glyph_arg;
	size_t						contours_limits;

	draw_glyph_arg.points = (t_vector2f *)points;
	draw_glyph_arg.nb_of_points = sizeof(points) / sizeof(*points);
	contours_limits = draw_glyph_arg.nb_of_points;
	draw_glyph_arg.contours_limits = &contours_limits;
	draw_glyph_arg.nb_of_contours = 1;
	draw_glyph_arg.bounds = (t_glyph_outline_bounds){points[0].x, points[3].y,
		points[2].x, points[1].y};
	draw_glyph(&draw_glyph_arg, (image->width - border * 2) / 10.f, image,
		color, border, border);
}
