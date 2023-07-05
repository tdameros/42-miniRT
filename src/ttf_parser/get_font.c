/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_font.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:53:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/27 18:53:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "font/render.h"

static int	get_points(t_glyph_generated_points *points, uint8_t i,
				const t_ttf *ttf);
static void	reverse_y(t_vector2f *points, size_t size, float y_max);
static void	get_glyph_bounds(t_glyph_generated_points *points);

int	get_font(t_font *font, char *font_file)
{
	t_ttf	ttf;
	uint8_t	i;

	font->glyphs = ft_calloc(127, sizeof(*font->glyphs));
	font->long_hor_metric = malloc(sizeof(*font->long_hor_metric) * 127);
	if (font->glyphs == NULL || font->long_hor_metric == NULL)
	{
		free(font->glyphs);
		free(font->long_hor_metric);
		return (-1);
	}
	if (ttf_parser(&ttf, font_file) < 0)
	{
		free(font->glyphs);
		free(font->long_hor_metric);
		return (-1);
	}
	i = -1;
	while (++i < 127)
	{
		if (get_points(font->glyphs + i, i, &ttf) < 0)
		{
			free(font->glyphs); // TODO free triangles data
			free(font->long_hor_metric);
			destroy_t_ttf(&ttf);
			return (-1);
		}
		font->long_hor_metric[i] = get_long_hor_metric(i, &ttf);
	}
	font->bounds.yMax = ttf.head.yMax;
	font->bounds.xMax = ttf.head.xMax;
	font->bounds.yMin = ttf.head.yMin;
	font->bounds.xMin = ttf.head.xMin;
	destroy_t_ttf(&ttf);
	return (0);
}

static int	get_points(t_glyph_generated_points *points,
				const uint8_t i, const t_ttf *ttf)
{
	const t_glyph_outline	*glyph = ttf->glyphs + get_glyph_index(i, ttf);
	t_vector				vector_points;

	if (glyph->numberOfContours <= 0)
	{
		ft_bzero(points, sizeof(*points));
		return (0);
	}
	if (get_glyph_points(&vector_points, glyph, &points->contours_limits) < 0)
	{
		ft_bzero(points, sizeof(*points));
		return (-1);
	}
	ft_vector_minimize_size(&vector_points);
	points->points = vector_points.data;
	points->nb_of_points = vector_points.length;
	points->nb_of_contours = glyph->numberOfContours;
	reverse_y(points->points, points->nb_of_points, ttf->head.yMax);
	get_glyph_bounds(points);
	return (0);
}

static void	reverse_y(t_vector2f *points, size_t size, float y_max)
{
	while (size--)
		points[size].y = (1.f - points[size].y / y_max) * y_max;
}

static void	get_glyph_bounds(t_glyph_generated_points *points)
{
	t_vector2f	min;
	t_vector2f	max;
	size_t		i;

	min = (t_vector2f){FLT_MAX, FLT_MAX};
	max = (t_vector2f){FLT_MIN, FLT_MIN};
	i = points->nb_of_points;
	while (i--)
	{
		min.x = fminf(min.x, points->points[i].x);
		min.y = fminf(min.y, points->points[i].y);
		max.x = fmaxf(max.x, points->points[i].x);
		max.y = fmaxf(max.y, points->points[i].y);
	}
	points->bounds = (t_glyph_outline_bounds){
		.xMin = min.x,
		.xMax = max.x + (max.x - (int)max.x != 0.f),
		.yMin = min.y,
		.yMax = max.y + (max.y - (int)max.y != 0.f)};
}
