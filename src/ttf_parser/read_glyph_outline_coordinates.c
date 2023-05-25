/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_glyph_outline_coordinates.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:11:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/22 22:11:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ttf.h"

static int	read_current_coordinate(const t_string *file, size_t *file_cursor,
				int16_t *current_coordinate, uint8_t flag_combined);

int	read_x_coordinates(const t_string *file, size_t *file_cursor,
		t_glyph_outline *outline, uint16_t last_index)
{
	uint32_t	i;
	int16_t		prev_coordinate;
	int16_t		current_coordinate;
	uint8_t		flag_combined;

	outline->xCoordinates = malloc((last_index + 1) * 2);
	if (outline->xCoordinates == NULL)
		return (-1);
	prev_coordinate = 0;
	current_coordinate = 0;
	i = -1;
	while (++i < last_index + 1)
	{
		flag_combined = outline->flags[i].x_short << 1
			| outline->flags[i].x_short_pos;
		if (read_current_coordinate(file, file_cursor, &current_coordinate,
				flag_combined) < 0)
			return (free(outline->xCoordinates), -1);
		outline->xCoordinates[i] = current_coordinate + prev_coordinate;
		prev_coordinate = outline->xCoordinates[i];
	}
	return (0);
}

int	read_y_coordinates(const t_string *file, size_t *file_cursor,
		t_glyph_outline *outline, uint16_t last_index)
{
	uint32_t	i;
	int16_t		prev_coordinate;
	int16_t		current_coordinate;
	uint8_t		flag_combined;

	outline->yCoordinates = malloc((last_index + 1) * 2);
	if (outline->yCoordinates == NULL)
		return (-1);
	prev_coordinate = 0;
	current_coordinate = 0;
	i = -1;
	while (++i < last_index + 1)
	{
		flag_combined = outline->flags[i].y_short << 1
			| outline->flags[i].y_short_pos;
		if (read_current_coordinate(file, file_cursor, &current_coordinate,
				flag_combined) < 0)
			return (free(outline->yCoordinates), -1);
		outline->yCoordinates[i] = current_coordinate + prev_coordinate;
		prev_coordinate = outline->yCoordinates[i];
	}
	return (0);
}

static int	read_current_coordinate(const t_string *file, size_t *file_cursor,
				int16_t *current_coordinate, uint8_t flag_combined)
{
	uint8_t	tmp;

	if (flag_combined == 0)
	{
		if (read_int16_move(file, file_cursor, current_coordinate) < 0)
			return (-1);
	}
	else if (flag_combined == 1)
		*current_coordinate = 0;
	else if (flag_combined == 2)
	{
		if (read_uint8_move(file, file_cursor, &tmp)
			< 0)
			return (-1);
		*current_coordinate = -tmp;
	}
	else if (flag_combined == 3)
	{
		if (read_uint8_move(file, file_cursor, &tmp)
			< 0)
			return (-1);
		*current_coordinate = tmp;
	}
	return (0);
}
