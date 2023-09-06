/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_centered_number_to_image.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 01:43:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/28 01:43:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "float.h"

#include "engine.h"
#include "font/render.h"

// BORDER should not be < 0
#define BORDER 4

static t_vector2f	get_glyphs_size(const t_font *font, const char *number);
static float		get_glyphs_y_min(const t_font *font, const char *number);
static void			write_character(char c, const t_font *font, t_image *image,
						t_write_character_data write_character_data);

void	write_centered_number_to_image(const t_font *font, t_image *image,
			const char *number)
{
	const t_vector2f	glyphs_max_size = get_glyphs_size(font, number);
	const float			scale = fminf(
			(image->width - BORDER * 2) / glyphs_max_size.x,
			(image->height - BORDER * 2) / glyphs_max_size.y);
	t_vector2f			offsets;
	size_t				i;
	bool				is_decimal;

	is_decimal = false;
	offsets.y = (image->height - scale * glyphs_max_size.y)
		/ 2.f - get_glyphs_y_min(font, number) * scale;
	offsets.x = BORDER + (image->width - BORDER * 2) / 2.f
		- glyphs_max_size.x * scale / 2.f;
	i = 0;
	while (number[i]
		&& offsets.x + font->long_hor_metric[(int8_t)number[i]].advanceWidth
		* scale < image->width)
	{
		write_character(number[i], font, image,
			(t_write_character_data){scale, &offsets, &is_decimal});
		i++;
	}
}

static t_vector2f	get_glyphs_size(const t_font *font, const char *number)
{
	t_vector2f	result;
	size_t		i;

	result = (t_vector2f){0.f, FLT_MIN};
	i = -1;
	while (number[++i] != '\0')
	{
		result.x += font->long_hor_metric[(int8_t)number[i]].advanceWidth;
		result.y = fmaxf(result.y, font->glyphs[(int8_t)number[i]].bounds.yMax
				- font->glyphs[(int8_t)number[i]].bounds.yMin);
	}
	return (result);
}

static float	get_glyphs_y_min(const t_font *font, const char *number)
{
	size_t	i;
	float	result;

	result = FLT_MAX;
	i = -1;
	while (number[++i] != '\0')
		result = fminf(result, font->glyphs[(int8_t)number[i]].bounds.yMin);
	return (result);
}

static void	write_character(const char c, const t_font *font, t_image *image,
				const t_write_character_data write_character_data)
{
	const float	scale = write_character_data.scale;
	t_vector2f	*offsets;
	bool		*is_decimal;

	is_decimal = write_character_data.is_decimal;
	offsets = write_character_data.offsets;
	if (c == '.')
		*is_decimal = true;
	if (*is_decimal)
		draw_glyph(font->glyphs + c, (t_draw_glyph_data){scale, image,
			COLOR_LIGHT_GREY, offsets->x
			+ font->long_hor_metric[(int8_t)c].leftSideBearing * scale,
			offsets->y});
	else
		draw_glyph(font->glyphs + c, (t_draw_glyph_data){scale, image,
			COLOR_WHITE, offsets->x
			+ font->long_hor_metric[(int8_t)c].leftSideBearing * scale,
			offsets->y});
	offsets->x += font->long_hor_metric[(int8_t)c].advanceWidth * scale;
}
