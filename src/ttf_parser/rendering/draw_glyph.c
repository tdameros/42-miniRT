/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_glyph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:36:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/25 14:36:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "font/render.h"

// PIXEL_DIVISION should be >= 1 (1 means no anti aliasing)
#define PIXEL_DIVISION 3.f

static t_glyph_generated_points	get_adjusted_points(
									const t_glyph_generated_points *raw_points,
									float scale, float x_offset,
									float y_offset);
static bool						is_point_inside_glyph(t_vector2f point,
									const t_glyph_generated_points *points);
static int						add_intersection(t_segment segment_1,
									t_segment segment_2);

void	draw_glyph(const t_glyph_generated_points *raw_points,
			const float scale, t_image *image, const unsigned int color,
			const float x_offset, const float y_offset)
{
	const t_glyph_generated_points	points = get_adjusted_points(raw_points,
			scale, x_offset, y_offset);
	int								x;
	int								y;
	const t_color					color_vec = get_t_color_from_uint(color);
	unsigned int					*dst;
	int								nb_of_points_in_triangle;

	if (points.points == NULL)
		return ;
	y = points.bounds.yMin * scale - 1;
	while (++y <= points.bounds.yMax)
	{
		x = points.bounds.xMin - 1;
		while (++x <= points.bounds.xMax)
		{
			dst = image->address + y * image->width + x;
			if (dst < image->address)
				continue ;
			if (dst >= image->limit)
				return (free(points.points));
			nb_of_points_in_triangle = 0;
			for (int sub_y = 0; sub_y < PIXEL_DIVISION; sub_y++)
				for (int sub_x = 0; sub_x < PIXEL_DIVISION; sub_x++)
					nb_of_points_in_triangle += is_point_inside_glyph(
							(t_vector2f){x + sub_x / PIXEL_DIVISION + 1.f / PIXEL_DIVISION / 2,
										 y + sub_y / PIXEL_DIVISION + 1.f / PIXEL_DIVISION / 2}, &points);
			if (nb_of_points_in_triangle > 0)
			{
				t_color new_color = vector3f_multiply(color_vec, nb_of_points_in_triangle);
				new_color = vector3f_add(new_color, vector3f_multiply(get_t_color_from_uint(*dst), PIXEL_DIVISION * PIXEL_DIVISION - nb_of_points_in_triangle));
				new_color = vector3f_divide(new_color, PIXEL_DIVISION * PIXEL_DIVISION);
				*dst = vec_rgb_to_uint(new_color);
			}
//			if (is_point_inside_glyph((t_vector2f){x + 0.5f, y + 0.5f}, &points))
//				*dst = color;
		}
	}
	free(points.points);
}

static t_glyph_generated_points	get_adjusted_points(
									const t_glyph_generated_points *raw_points,
									const float scale, const float x_offset,
									const float y_offset)
{
	t_glyph_generated_points	result;
	size_t						i;

	result.points = malloc(sizeof(*result.points) * raw_points->nb_of_points);
	if (result.points == NULL)
	{
		ft_print_error("Failed to draw glyph, allocation failed\n");
		return (result);
	}
	i = raw_points->nb_of_points;
	while (i--)
	{
		result.points[i] = vector2f_multiply(raw_points->points[i], scale);
		result.points[i].x += x_offset;
		result.points[i].y += y_offset;
	}
	result.nb_of_points = raw_points->nb_of_points;
	result.bounds = (t_glyph_outline_bounds){
		.xMin = raw_points->bounds.xMin * scale + x_offset,
		.xMax = raw_points->bounds.xMax * scale + x_offset,
		.yMin = raw_points->bounds.yMin * scale + y_offset,
		.yMax = raw_points->bounds.yMax * scale + y_offset};
	result.bounds.xMax += (result.bounds.xMax - (int)result.bounds.xMax != 0.f);
	result.bounds.yMax += (result.bounds.yMax - (int)result.bounds.yMax != 0.f);
	result.nb_of_contours = raw_points->nb_of_contours;
	result.contours_limits = raw_points->contours_limits;
	return (result);
}

static bool	is_point_inside_glyph(t_vector2f point,
				const t_glyph_generated_points *points)
{
	int16_t			contour;
	size_t			contour_start;
	size_t			i;
	const t_segment	segment = {point,
		(t_vector2f){points->bounds.xMax + 100.f, points->bounds.yMax}};
	size_t			nb_of_intersected_segments;

	nb_of_intersected_segments = 0;
	contour = -1;
	while (++contour < points->nb_of_contours)
	{
		if (contour != 0)
			contour_start = points->contours_limits[contour - 1];
		else
			contour_start = 0;
		i = contour_start - 1;
		while (++i < points->contours_limits[contour] - 1)
			nb_of_intersected_segments += add_intersection(segment,
					(t_segment){points->points[i], points->points[i + 1]});
		nb_of_intersected_segments += add_intersection(segment,
				(t_segment){points->points[i], points->points[contour_start]});
	}
	return (nb_of_intersected_segments % 2);
}

static int	add_intersection(t_segment segment_1, t_segment segment_2)
{
	t_segment	corrected_segment_1;

	if ((vector2f_are_equal(segment_1.a, segment_2.a)
			|| vector2f_are_equal(segment_1.a, segment_2.b))
		&& (vector2f_are_equal(segment_1.b, segment_2.a)
			|| vector2f_are_equal(segment_1.b, segment_2.b)))
		return (0);
	if (vector2f_are_equal(segment_1.a, segment_2.a)
		|| vector2f_are_equal(segment_1.a, segment_2.b))
		corrected_segment_1.a = vector2f_add(vector2f_multiply(
					vector2f_subtract(segment_1.b, segment_1.a), 0.05f),
				segment_1.a);
	else
		corrected_segment_1.a = segment_1.a;
	if (vector2f_are_equal(segment_1.b, segment_2.a)
		|| vector2f_are_equal(segment_1.b, segment_2.b))
		corrected_segment_1.b = vector2f_add(vector2f_multiply(
					vector2f_subtract(segment_1.a, segment_1.b), 0.05f),
				segment_1.b);
	else
		corrected_segment_1.b = segment_1.b;
	return (do_segments_intersect(corrected_segment_1.a, corrected_segment_1.b,
			segment_2.a, segment_2.b));
}
