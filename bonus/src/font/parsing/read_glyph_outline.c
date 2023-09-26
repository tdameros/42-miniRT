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

static int	read_end_points_of_contours(const t_string *file,
				size_t *file_cursor, t_glyph_outline *outline);
static int	read_instructions(const t_string *file, size_t *file_cursor,
				t_glyph_outline *outline);
static int	read_flags(const t_string *file, size_t *file_cursor,
				t_glyph_outline *outline, uint16_t last_index);

int	read_glyph_outline(const t_string *file, size_t offset,
		t_glyph_outline *outline)
{
	uint16_t		last_index;

	ft_bzero(outline, sizeof(*outline));
	if (read_int16_move(file, &offset, &outline->number_of_contours) < 0)
		return (-1);
	if (outline->number_of_contours <= 0)
		return (0);
	if (read_int16_move(file, &offset, &outline->bounds.x_min) < 0
		|| read_int16_move(file, &offset, &outline->bounds.y_min) < 0
		|| read_int16_move(file, &offset, &outline->bounds.x_max) < 0
		|| read_int16_move(file, &offset, &outline->bounds.y_max) < 0
		|| read_end_points_of_contours(file, &offset, outline) < 0)
		return (-1);
	if (read_instructions(file, &offset, outline) < 0)
		return (free(outline->end_pts_of_contours), -1);
	last_index = outline->end_pts_of_contours[outline->number_of_contours - 1];
	if (read_flags(file, &offset, outline, last_index) < 0
		|| read_x_coordinates(file, &offset, outline, last_index) < 0
		|| read_y_coordinates(file, &offset, outline, last_index) < 0)
		return (free(outline->end_pts_of_contours), free(outline->instructions),
			free(outline->flags), free(outline->x_coordinates), -1);
	return (0);
}

static int	read_end_points_of_contours(const t_string *file,
				size_t *file_cursor, t_glyph_outline *outline)
{
	size_t			i;
	const size_t	number_of_contours = outline->number_of_contours;

	outline->end_pts_of_contours = malloc(
			sizeof(*outline->end_pts_of_contours) * number_of_contours);
	if (outline->end_pts_of_contours == NULL)
		return (-1);
	i = -1;
	while (++i < number_of_contours)
		if (read_uint16_move(file, file_cursor,
				outline->end_pts_of_contours + i) < 0)
			return (free(outline->end_pts_of_contours), -1);
	return (0);
}

static int	read_instructions(const t_string *file, size_t *file_cursor,
				t_glyph_outline *outline)
{
	uint16_t	i;

	if (read_uint16_move(file, file_cursor, &outline->instruction_length) < 0)
		return (-1);
	outline->instructions = malloc(
			sizeof(*outline->instructions) * outline->instruction_length);
	if (outline->instructions == NULL)
		return (-1);
	i = -1;
	while (++i < outline->instruction_length)
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
			while (repeat_count-- > 0 && i + 1 < size)
			{
				i++;
				outline->flags[i] = outline->flags[i - 1];
			}
		}
	}
	return (0);
}
