/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:50:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:38:59 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "image.h"
#include "math/vector.h"
#include "colors.h"
#include "libft.h"
#include "font/rendering_structs.h"
#include "font/render.h"

#define PIXEL_DIVISION 3.f

static void	draw_circle_pixel(unsigned int *dst, t_vector2f pixel,
				unsigned int circle_color, t_circle_info circle);
static bool	is_point_in_circle(t_vector2f pixel, t_circle_info circle,
				float sub_x, float sub_y);

void	image_draw_circle(t_image *image, const t_vector2f circle_center,
			const float radius, const unsigned int color)
{
	const t_circle_info	circle = {circle_center, radius * radius};
	int					y_offset;
	int					y;
	int					x;

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
			draw_circle_pixel(image->address + y_offset + x, (t_vector2f){x, y},
				color, circle);
			x++;
		}
		y_offset += image->line_length;
		y++;
	}
}
#include "stdio.h"
static void	draw_circle_pixel(unsigned int *dst, const t_vector2f pixel,
				const unsigned int circle_color, t_circle_info circle)
{
	int		sub_y;
	int		sub_x;
	int		nb_of_points_in_circle;
	t_color	new_color;
	int		transparency;

	nb_of_points_in_circle = 0;
	sub_y = -1;
	while (++sub_y < PIXEL_DIVISION)
	{
		sub_x = -1;
		while (++sub_x < PIXEL_DIVISION)
			nb_of_points_in_circle += is_point_in_circle(pixel, circle, sub_x,
					sub_y);
	}
	if (nb_of_points_in_circle <= 0)
		return ;
	new_color = vector3f_multiply(get_t_color_from_uint(circle_color),
			nb_of_points_in_circle);
	new_color = vector3f_add(new_color, vector3f_multiply(
			get_t_color_from_uint(*dst), PIXEL_DIVISION * PIXEL_DIVISION
				- nb_of_points_in_circle));
	new_color = vector3f_divide(new_color, PIXEL_DIVISION * PIXEL_DIVISION);
	transparency = (get_transparency(circle_color) * nb_of_points_in_circle
		+ get_transparency(*dst) * (PIXEL_DIVISION * PIXEL_DIVISION
		  - nb_of_points_in_circle)) / (PIXEL_DIVISION * PIXEL_DIVISION);
	*dst = vec_rgb_to_uint(new_color) | (transparency << 24);
}

static bool	is_point_in_circle(const t_vector2f pixel,
				const t_circle_info circle, const float sub_x,
				const float sub_y)
{
	const float	x = pixel.x + sub_x / PIXEL_DIVISION + 1.f / PIXEL_DIVISION / 2;
	const float	y = pixel.y + sub_y / PIXEL_DIVISION + 1.f / PIXEL_DIVISION / 2;

	return (powf(x - circle.circle_center.x, 2.f)
		+ powf(y - circle.circle_center.y, 2.f) <= circle.radius_squared);
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
	draw_glyph(&draw_glyph_arg, (t_draw_glyph_data){1.f, image, color, 0, 0});
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
	draw_glyph(&draw_glyph_arg, (t_draw_glyph_data){1.f, image, color, 0, 0});
}
