/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_top_rectangles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:35:59 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:36:02 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "colors.h"
#include "gui/utils.h"
#include "font/render.h"

static void	draw_top_rectangle(t_image *image, unsigned int color,
				float scale, t_vector2f offset);
static void	draw_top_right_rectangle(t_image *image, unsigned int color,
				float scale, t_vector2f offset);
static void	draw_top_left_rectangle(t_image *image, unsigned int color,
				float scale, t_vector2f offset);

void	draw_top_rectangles(t_image *image, const unsigned int color,
			const float scale, const t_vector2f offset)
{
	draw_top_left_rectangle(image, color, scale, offset);
	draw_top_rectangle(image, color, scale, offset);
	draw_top_right_rectangle(image, color, scale, offset);
}

static void	draw_top_rectangle(t_image *image, const unsigned int color,
				const float scale, const t_vector2f offset)
{
	const t_vector2f			points[] = {
		(t_vector2f){481.f, 40.f},
		(t_vector2f){547.f, 40.f},
		(t_vector2f){547.f, 167.f},
		(t_vector2f){481.f, 167.f}};
	t_glyph_generated_points	draw_glyph_arg;
	size_t						contours_limits;

	draw_glyph_arg.points = (t_vector2f *)points;
	draw_glyph_arg.nb_of_points = sizeof(points) / sizeof(*points);
	contours_limits = draw_glyph_arg.nb_of_points;
	draw_glyph_arg.contours_limits = &contours_limits;
	draw_glyph_arg.nb_of_contours = 1;
	draw_glyph_arg.bounds = (t_glyph_outline_bounds){points[0].x, points[0].y, \
													points[1].x, points[3].y};
	draw_glyph(&draw_glyph_arg, (t_draw_glyph_data){scale, image, color, \
													offset.x, offset.y});
}

static void	draw_top_right_rectangle(t_image *image, const unsigned int color,
				const float scale, const t_vector2f offset)
{
	const t_vector2f			points[] = {
		(t_vector2f){824.f, 157.f},
		(t_vector2f){871.f, 203.f},
		(t_vector2f){780.f, 293.f},
		(t_vector2f){734.f, 247.f}};
	t_glyph_generated_points	draw_glyph_arg;
	size_t						contours_limits;

	draw_glyph_arg.points = (t_vector2f *)points;
	draw_glyph_arg.nb_of_points = sizeof(points) / sizeof(*points);
	contours_limits = draw_glyph_arg.nb_of_points;
	draw_glyph_arg.contours_limits = &contours_limits;
	draw_glyph_arg.nb_of_contours = 1;
	draw_glyph_arg.bounds = (t_glyph_outline_bounds){points[3].x, points[0].y, \
													points[1].x, points[2].y};
	draw_glyph(&draw_glyph_arg, (t_draw_glyph_data){scale, image, color, \
													offset.x, offset.y});
}

static void	draw_top_left_rectangle(t_image *image, const unsigned int color,
				const float scale, const t_vector2f offset)
{
	const t_vector2f			points[] = {
		(t_vector2f){156.f, 199.f},
		(t_vector2f){203.f, 152.f},
		(t_vector2f){293.f, 242.f},
		(t_vector2f){246.f, 298.f}};
	t_glyph_generated_points	draw_glyph_arg;
	size_t						contours_limits;

	draw_glyph_arg.points = (t_vector2f *)points;
	draw_glyph_arg.nb_of_points = sizeof(points) / sizeof(*points);
	contours_limits = draw_glyph_arg.nb_of_points;
	draw_glyph_arg.contours_limits = &contours_limits;
	draw_glyph_arg.nb_of_contours = 1;
	draw_glyph_arg.bounds = (t_glyph_outline_bounds){points[0].x, points[1].y, \
													points[2].x, points[3].y};
	draw_glyph(&draw_glyph_arg, (t_draw_glyph_data){scale, image, color, \
													offset.x, offset.y});
}
