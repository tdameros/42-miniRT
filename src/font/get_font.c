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
#include "float.h"

#include "font/render.h"

static int	get_font_data(t_font *font, t_ttf *ttf);
static int	get_points(t_glyph_generated_points *points, uint8_t i,
				const t_ttf *ttf);
static void	get_glyph_bounds(t_glyph_generated_points *points);
static void	free_font_glyphs(t_glyph_generated_points *glyphs, uint8_t i);

int	get_font(t_font *font, char *font_file)
{
	t_ttf	ttf;

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
	if (get_font_data(font, &ttf) < 0)
		return (-1);
	destroy_t_ttf(&ttf);
	return (0);
}

static int	get_font_data(t_font *font, t_ttf *ttf)
{
	uint8_t	i;

	i = -1;
	while (++i < 127)
	{
		if (get_points(font->glyphs + i, i, ttf) < 0)
		{
			free_font_glyphs(font->glyphs, i);
			free(font->long_hor_metric);
			destroy_t_ttf(ttf);
			return (-1);
		}
		font->long_hor_metric[i] = get_long_hor_metric(i, ttf);
	}
	font->bounds.y_max = ttf->head.y_max;
	font->bounds.x_max = ttf->head.x_max;
	font->bounds.y_min = ttf->head.y_min;
	font->bounds.x_min = ttf->head.x_min;
	return (0);
}

static int	get_points(t_glyph_generated_points *points,
				const uint8_t i, const t_ttf *ttf)
{
	const t_glyph_outline	*glyph = ttf->glyphs + get_glyph_index(i, ttf);
	t_vector				vector_points;
	size_t					j;

	if (glyph->number_of_contours <= 0)
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
	points->nb_of_contours = glyph->number_of_contours;
	j = points->nb_of_points;
	while (j--)
		points->points[j].y = (1.f - points->points[j].y / ttf->head.y_max)
			* ttf->head.y_max;
	get_glyph_bounds(points);
	return (0);
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
		.x_min = min.x,
		.x_max = max.x + (max.x - (int)max.x != 0.f),
		.y_min = min.y,
		.y_max = max.y + (max.y - (int)max.y != 0.f)};
}

static void	free_font_glyphs(t_glyph_generated_points *glyphs, uint8_t i)
{
	while (i--)
	{
		free(glyphs[i].points);
		free(glyphs[i].contours_limits);
	}
	free(glyphs);
}
