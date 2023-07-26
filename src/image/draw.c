/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:50:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/05 13:50:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "image.h"
#include "math/vector.h"
#include "colors.h"
#include "libft.h"
#include "font/rendering_structs.h"
#include "font/render.h"

void	image_draw_circle(t_image *image, const t_vector2i circle_center,
			const float radius, const unsigned int color)
{
	const float	radius_squared = radius * radius;
	int			y_offset;
	int			y;
	int			x;

	y = circle_center.y - radius - 1;
	if (y < 0)
		y = 0;
	y_offset = image->width * (y + 1);
	while (y < image->height && y < circle_center.y + (int)radius + 1)
	{
		x = circle_center.x - radius - 1;
		if (x < 0)
			x = 0;
		while (x < image->width && x < circle_center.x + (int)radius + 1)
		{
			if (powf(x - circle_center.x, 2.f) + powf(y - circle_center.y, 2.f)
				<= radius_squared)
				image->address[y_offset + x] = color;
			x++;
		}
		y_offset += image->line_length;
		y++;
	}
}

void	image_draw_plus(t_image *image, const float thickness,
			const float border, const unsigned int color)
{
	const t_vector2f			points[] = {\
		{(image->width - thickness) / 2.f, border}, \
		{(image->width + thickness) / 2.f, border}, \
		{(image->width + thickness) / 2.f, (image->height - thickness) / 2.f}, \
		{image->width - border, (image->height - thickness) / 2.f}, \
		{image->width - border, (image->height + thickness) / 2.f}, \
		{(image->width + thickness) / 2.f, (image->height + thickness) / 2.f}, \
		{(image->width + thickness) / 2.f, image->height - border}, \
		{(image->width - thickness) / 2.f, image->height - border}, \
		{(image->width - thickness) / 2.f, (image->height + thickness) / 2.f}, \
		{border, (image->height + thickness) / 2.f}, \
		{border, (image->height - thickness) / 2.f}, \
		{(image->width - thickness) / 2.f, (image->height - thickness) / 2.f}
	};
	t_glyph_generated_points	draw_glyph_arg;
	size_t						contours_limits;

	draw_glyph_arg.points = (t_vector2f *)points;
	draw_glyph_arg.nb_of_points = sizeof(points) / sizeof(*points);
	contours_limits = draw_glyph_arg.nb_of_points;
	draw_glyph_arg.contours_limits = &contours_limits;
	draw_glyph_arg.nb_of_contours = 1;
	draw_glyph_arg.bounds = (t_glyph_outline_bounds){points[10].x, points[0].y,
		points[3].x, points[6].y};
	draw_glyph(&draw_glyph_arg, 1.f, image, color, 0.f, 0.f);
}

void	image_draw_minus(t_image *image, const int thickness,
			const int border, const unsigned int color)
{
	const t_vector2f			points[] = {\
		{border, (image->height - thickness) / 2.f}, \
		{image->width - border, (image->height - thickness) / 2.f}, \
		{image->width - border, (image->height + thickness) / 2.f}, \
		{border, (image->height + thickness) / 2.f}
	};
	t_glyph_generated_points	draw_glyph_arg;
	size_t						contours_limits;

	draw_glyph_arg.points = (t_vector2f *)points;
	draw_glyph_arg.nb_of_points = sizeof(points) / sizeof(*points);
	contours_limits = draw_glyph_arg.nb_of_points;
	draw_glyph_arg.contours_limits = &contours_limits;
	draw_glyph_arg.nb_of_contours = 1;
	draw_glyph_arg.bounds = (t_glyph_outline_bounds){points[0].x, points[0].y,
		points[2].x, points[2].y};
	draw_glyph(&draw_glyph_arg, 1.f, image, color, 0.f, 0.f);
}