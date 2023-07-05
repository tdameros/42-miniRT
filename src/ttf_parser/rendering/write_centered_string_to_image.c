/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_centered_string_to_image.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 01:43:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/28 01:43:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <float.h>

#include "engine.h"
#include "font/render.h"

// BORDER should not be <= 0
#define BORDER 4

static t_vector2f	get_glyphs_size(const t_font *font, const char *string);
static float		get_glyphs_y_min(const t_font *font, const char *string);

void	write_centered_string_to_image(const t_font *font, t_image *image,
			const char *string)
{
	const t_vector2f	glyphs_max_size = get_glyphs_size(font, string);
	const float			scale = fminf(
			(image->width - BORDER * 2) / glyphs_max_size.x,
			(image->height - BORDER * 2) / glyphs_max_size.y);
	const float			y_offset = (image->height - scale * glyphs_max_size.y)
		/ 2.f - get_glyphs_y_min(font, string) * scale;
	float				x_offset;
	size_t				i;

	x_offset = BORDER + (image->width - BORDER * 2) / 2.f
		- glyphs_max_size.x * scale / 2.f;
	i = 0;
	while (string[i]
		&& x_offset + font->long_hor_metric[(int8_t)string[i]].advanceWidth * scale <= image->width - BORDER)
	{
		draw_glyph(font->glyphs + string[i], scale, image, COLOR_WHITE,
			x_offset + font->long_hor_metric[(int8_t)string[i]].leftSideBearing * scale,
			y_offset);
		x_offset += font->long_hor_metric[(int8_t)string[i]].advanceWidth * scale;
		i++;
	}
}

static t_vector2f	get_glyphs_size(const t_font *font, const char *string)
{
	t_vector2f	result;
	size_t		i;

	result = (t_vector2f){0.f, FLT_MIN};
	i = -1;
	while (string[++i] != '\0')
	{
		result.x += font->long_hor_metric[(int8_t)string[i]].advanceWidth;
		result.y = fmaxf(result.y, font->glyphs[(int8_t)string[i]].bounds.yMax
				- font->glyphs[(int8_t)string[i]].bounds.yMin);
	}
	return (result);
}

static float	get_glyphs_y_min(const t_font *font, const char *string)
{
	size_t	i;
	float	result;

	result = FLT_MAX;
	i = -1;
	while (string[++i] != '\0')
		result = fminf(result, font->glyphs[(int8_t)string[i]].bounds.yMin);
	return (result);
}
