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
#include "float.h"

#include "engine.h"
#include "font/render.h"

// BORDER should not be < 0
#define BORDER 4

static t_vector2f	get_glyphs_size(const t_font *font, const char *string);
static float		get_glyphs_y_min(const t_font *font, const char *string);
static void			write_character(char c, const t_font *font, t_image *image,
						t_write_character_data write_character_data);

void	write_centered_string_to_image(const t_font *font, t_image *image,
			const char *string)
{
	const t_vector2f	glyphs_max_size = get_glyphs_size(font, string);
	const float			scale = fminf(
			(image->width - BORDER * 2) / glyphs_max_size.x,
			(image->height - BORDER * 2) / glyphs_max_size.y);
	t_vector2f			offsets;
	size_t				i;

	offsets.y = (image->height - scale * glyphs_max_size.y)
		/ 2.f - get_glyphs_y_min(font, string) * scale;
	offsets.x = BORDER + (image->width - BORDER * 2) / 2.f
		- glyphs_max_size.x * scale / 2.f;
	i = 0;
	while (string[i]
		&& offsets.x + font->long_hor_metric[(int8_t)string[i]].advance_width
		* scale < image->width)
	{
		write_character(string[i], font, image,
			(t_write_character_data){scale, &offsets, NULL});
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
		result.x += font->long_hor_metric[(int8_t)string[i]].advance_width;
		if (string[i] == ' ')
			continue ;
		result.y = fmaxf(result.y, font->glyphs[(int8_t)string[i]].bounds.y_max
				- font->glyphs[(int8_t)string[i]].bounds.y_min);
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
	{
		if (string[i] == ' ')
			continue ;
		result = fminf(result, font->glyphs[(int8_t)string[i]].bounds.y_min);
	}
	return (result);
}

static void	write_character(const char c, const t_font *font, t_image *image,
				const t_write_character_data write_character_data)
{
	const float	scale = write_character_data.scale;
	t_vector2f	*offsets;

	offsets = write_character_data.offsets;
	if (c != ' ')
		draw_glyph(font->glyphs + c, (t_draw_glyph_data){scale, image,
			COLOR_WHITE, offsets->x
			+ font->long_hor_metric[(int8_t)c].left_side_bearing * scale,
			offsets->y});
	offsets->x += font->long_hor_metric[(int8_t)c].advance_width * scale;
}
