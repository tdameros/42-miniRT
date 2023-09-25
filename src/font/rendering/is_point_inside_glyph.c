/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_point_inside_glyph.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:42:34 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 01:42:34 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font/render.h"

static int	add_intersection(t_segment segment_1, t_segment segment_2);

bool	is_point_inside_glyph(t_vector2f point,
				const t_glyph_generated_points *points)
{
	int16_t			contour;
	size_t			contour_start;
	size_t			i;
	const t_segment	segment = {point,
		(t_vector2f){points->bounds.x_max + 100.f, points->bounds.y_max}};
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
