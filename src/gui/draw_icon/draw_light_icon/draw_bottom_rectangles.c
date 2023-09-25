/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bottom_rectangles.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:36:04 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:36:05 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "colors.h"
#include "gui/utils.h"
#include "font/render.h"

static void	draw_bottom_rectangle(t_image *image, unsigned int color,
				float scale, t_vector2f offset);
static void	draw_bottom_right_rectangle(t_image *image, unsigned int color,
				float scale, t_vector2f offset);
static void	draw_bottom_left_rectangle(t_image *image, unsigned int color,
				float scale, t_vector2f offset);

void	draw_bottom_rectangles(t_image *image, const unsigned int color,
			const float scale, const t_vector2f offset)
{
	draw_bottom_left_rectangle(image, color, scale, offset);
	draw_bottom_rectangle(image, color, scale, offset);
	draw_bottom_right_rectangle(image, color, scale, offset);
}

static void	draw_bottom_rectangle(t_image *image, const unsigned int color,
				const float scale, const t_vector2f offset)
{
	const t_vector2f			points[] = {
		(t_vector2f){541.f, 983.f},
		(t_vector2f){475.f, 983.f},
		(t_vector2f){475.f, 856.f},
		(t_vector2f){541.f, 856.f}};
	t_glyph_generated_points	draw_glyph_arg;
	size_t						contours_limits;

	draw_glyph_arg.points = (t_vector2f *)points;
	draw_glyph_arg.nb_of_points = sizeof(points) / sizeof(*points);
	contours_limits = draw_glyph_arg.nb_of_points;
	draw_glyph_arg.contours_limits = &contours_limits;
	draw_glyph_arg.nb_of_contours = 1;
	draw_glyph_arg.bounds = (t_glyph_outline_bounds){points[1].x, points[3].y, \
													points[0].x, points[1].y};
	draw_glyph(&draw_glyph_arg, (t_draw_glyph_data){scale, image, color, \
													offset.x, offset.y});
}

static void	draw_bottom_right_rectangle(t_image *image,
				const unsigned int color, const float scale,
				const t_vector2f offset)
{
	const t_vector2f			points[] = {
		(t_vector2f){868.f, 824.f},
		(t_vector2f){820.f, 872.f},
		(t_vector2f){730.f, 781.f},
		(t_vector2f){777.f, 734.f}};
	t_glyph_generated_points	draw_glyph_arg;
	size_t						contours_limits;

	draw_glyph_arg.points = (t_vector2f *)points;
	draw_glyph_arg.nb_of_points = sizeof(points) / sizeof(*points);
	contours_limits = draw_glyph_arg.nb_of_points;
	draw_glyph_arg.contours_limits = &contours_limits;
	draw_glyph_arg.nb_of_contours = 1;
	draw_glyph_arg.bounds = (t_glyph_outline_bounds){points[2].x, points[3].y, \
													points[0].x, points[1].y};
	draw_glyph(&draw_glyph_arg, (t_draw_glyph_data){scale, image, color, \
													offset.x, offset.y});
}

static void	draw_bottom_left_rectangle(t_image *image, const unsigned int color,
				const float scale, const t_vector2f offset)
{
	const t_vector2f			points[] = {
		(t_vector2f){199.f, 868.f},
		(t_vector2f){152.f, 819.f},
		(t_vector2f){241.f, 730.f},
		(t_vector2f){290.f, 778.f}};
	t_glyph_generated_points	draw_glyph_arg;
	size_t						contours_limits;

	draw_glyph_arg.points = (t_vector2f *)points;
	draw_glyph_arg.nb_of_points = sizeof(points) / sizeof(*points);
	contours_limits = draw_glyph_arg.nb_of_points;
	draw_glyph_arg.contours_limits = &contours_limits;
	draw_glyph_arg.nb_of_contours = 1;
	draw_glyph_arg.bounds = (t_glyph_outline_bounds){points[1].x, points[2].y, \
													points[3].x, points[0].y};
	draw_glyph(&draw_glyph_arg, (t_draw_glyph_data){scale, image, color, \
													offset.x, offset.y});
}
