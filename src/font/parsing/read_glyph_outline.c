/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_glyph_outline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:46:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/22 20:46:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "font/ttf_parser.h"

static int	read_endPtsOfContours(const t_string *file, size_t *file_cursor,
				t_glyph_outline *outline);
static int	read_instructions(const t_string *file, size_t *file_cursor,
				t_glyph_outline *outline);
static int	read_flags(const t_string *file, size_t *file_cursor,
				t_glyph_outline *outline, uint16_t last_index);

int	read_glyph_outline(const t_string *file, size_t offset,
		t_glyph_outline *outline)
{
	uint16_t		last_index;

	*outline = (t_glyph_outline){0};
	if (read_int16_move(file, &offset, &outline->numberOfContours) < 0)
		return (-1);
	if (outline->numberOfContours <= 0)
		return (0);
	if (read_int16_move(file, &offset, &outline->bounds.xMin) < 0)
		return (-1);
	if (read_int16_move(file, &offset, &outline->bounds.yMin) < 0)
		return (-1);
	if (read_int16_move(file, &offset, &outline->bounds.xMax) < 0)
		return (-1);
	if (read_int16_move(file, &offset, &outline->bounds.yMax) < 0)
		return (-1);
	if (read_endPtsOfContours(file, &offset, outline) < 0)
		return (-1);
	if (read_instructions(file, &offset, outline) < 0)
		return (free(outline->endPtsOfContours), -1);
	last_index = outline->endPtsOfContours[outline->numberOfContours - 1];
	if (read_flags(file, &offset, outline, last_index) < 0)
		return (free(outline->endPtsOfContours), free(outline->instructions),
			-1);
	if (read_x_coordinates(file, &offset, outline, last_index) < 0)
		return (free(outline->endPtsOfContours), free(outline->instructions),
			free(outline->flags), -1);
	if (read_y_coordinates(file, &offset, outline, last_index) < 0)
		return (free(outline->endPtsOfContours), free(outline->instructions),
			free(outline->flags), free(outline->xCoordinates), -1);
	return (0);
}

static int	read_endPtsOfContours(const t_string *file, size_t *file_cursor,
				t_glyph_outline *outline)
{
	size_t			i;
	const size_t	number_of_contours = outline->numberOfContours;

	outline->endPtsOfContours = malloc(sizeof(*outline->endPtsOfContours) * number_of_contours);
	if (outline->endPtsOfContours == NULL)
		return (-1);
	i = -1;
	while (++i < number_of_contours)
		if (read_uint16_move(file, file_cursor, outline->endPtsOfContours + i)
			< 0)
			return (free(outline->endPtsOfContours), -1);
	return (0);
}

static int	read_instructions(const t_string *file, size_t *file_cursor,
				t_glyph_outline *outline)
{
	uint16_t	i;

	if (read_uint16_move(file, file_cursor, &outline->instructionLength) < 0)
		return (-1);
	outline->instructions = malloc(sizeof(*outline->instructions) * outline->instructionLength);
	if (outline->instructions == NULL)
		return (-1);
	i = -1;
	while (++i < outline->instructionLength)
		if (read_uint8_move(file, file_cursor, outline->instructions + i) < 0)
			return (free(outline->instructions), -1);
	return (0);
}

static int	read_flags(const t_string *file, size_t *file_cursor,
				t_glyph_outline *outline, uint16_t last_index)
{
	const uint32_t	size = last_index + 1;
	size_t			i;
	uint8_t			repeat_count;

	outline->flags = malloc(sizeof(*outline->flags) * size);
	if (outline->flags == NULL)
		return (-1);
	i = -1;
	while (++i < size)
	{
		if (read_uint8_move(file, file_cursor, &outline->flags[i].flag) < 0)
			return (free(outline->flags), -1);
		if (outline->flags[i].repeat)
		{
			if (read_uint8_move(file, file_cursor, &repeat_count) < 0)
				return (free(outline->flags), -1);
			while (repeat_count-- > 0 && i + 1 < size) // TODO check why i + 1 is >= size on a valid font
			{
				i++;
				outline->flags[i] = outline->flags[i - 1];
			}
		}
	}
	return (0);
}
