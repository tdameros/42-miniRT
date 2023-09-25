/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_format4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 22:19:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 15:00:52 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "libft.h"

#include "font/ttf_parser.h"

static int	init_struct_variables(const t_string *file, t_format4 *format4,
				size_t i, uint16_t length);
static int	read_arrays_and_reserved_pad_content(const t_string *file,
				t_format4 *format4, size_t i, size_t i_starting_value);
static int	read_first_4_arrays(const t_string *file, t_format4 *format4,
				size_t i);
static int	read_glyph_id_array(const t_string *file, t_format4 *format4,
				size_t i, size_t i_starting_value);

int	read_format4(const t_string *file, t_ttf *ttf)
{
	uint16_t		length;
	size_t			i;

	i = ttf->cmap_offset + ttf->format4_offset;
	if (read_uint16(file, i + 2, &length) < 0)
		return (-1);
	if (length % 2 != 0)
		return (-1);
	ttf->format4 = ft_calloc(1, length + sizeof(t_format4)
			- sizeof(uint16_t) * 8);
	if (ttf->format4 == NULL)
	{
		perror("ft_calloc() failed");
		return (-1);
	}
	if (init_struct_variables(file, ttf->format4, i, length) < 0)
	{
		free(ttf->format4);
		return (-1);
	}
	return (0);
}

static int	init_struct_variables(const t_string *file, t_format4 *format4,
				size_t i, const uint16_t length)
{
	const size_t	i_starting_value = i;

	format4->format = read_uint16_unsafe(file->data + i);
	i += sizeof(uint16_t);
	format4->length = length;
	i += sizeof(uint16_t);
	if (read_uint16_move(file, &i, &format4->language) < 0
		|| read_uint16_move(file, &i, &format4->seg_count_x2) < 0
		|| format4->seg_count_x2 % 2 != 0
		|| length - sizeof(uint16_t) * 8 <= format4->seg_count_x2 * 4)
		return (-1);
	if (read_uint16_move(file, &i, &format4->search_range) < 0
		|| read_uint16_move(file, &i, &format4->entry_selector) < 0
		|| read_uint16_move(file, &i, &format4->range_shift) < 0)
		return (-1);
	format4->end_code = (uint16_t *)((uint8_t *)format4 + sizeof(t_format4));
	format4->start_code = format4->end_code + format4->seg_count_x2 / 2;
	format4->id_delta = format4->start_code + format4->seg_count_x2 / 2;
	format4->id_range_offset = format4->id_delta + format4->seg_count_x2 / 2;
	format4->glyph_id_array = format4->id_range_offset
		+ format4->seg_count_x2 / 2;
	if (read_arrays_and_reserved_pad_content(file, format4, i,
			i_starting_value) < 0)
		return (-1);
	return (0);
}

static int	read_arrays_and_reserved_pad_content(const t_string *file,
				t_format4 *format4, size_t i, const size_t i_starting_value)
{
	if (read_first_4_arrays(file, format4, i) < 0)
		return (-1);
	if (read_uint16(file, i + format4->seg_count_x2, &format4->reserved_pad) < 0
		|| format4->reserved_pad != 0)
		return (-1);
	i += format4->seg_count_x2 * 4 + sizeof(int16_t);
	return (read_glyph_id_array(file, format4, i, i_starting_value));
}

static int	read_first_4_arrays(const t_string *file, t_format4 *format4,
				size_t i)
{
	const size_t	start_code_start = i + format4->seg_count_x2
		+ sizeof(uint16_t);
	const size_t	id_delta_start = i + format4->seg_count_x2 * 2
		+ sizeof(uint16_t);
	const size_t	id_range_start = i + format4->seg_count_x2 * 3
		+ sizeof(uint16_t);
	uint			j;

	j = -1;
	while (++j < format4->seg_count_x2 / 2)
	{
		if (read_uint16(file, i + j * 2, format4->end_code + j) < 0)
			return (-1);
		if (read_uint16(file, start_code_start + j * 2,
				format4->start_code + j) < 0)
			return (-1);
		if (read_uint16(file, id_delta_start + j * 2,
				format4->id_delta + j) < 0)
			return (-1);
		if (read_uint16(file, id_range_start + j * 2,
				format4->id_range_offset + j) < 0)
			return (-1);
	}
	return (0);
}

static int	read_glyph_id_array(const t_string *file, t_format4 *format4,
				size_t i, const size_t i_starting_value)
{
	uint	j;
	size_t	remaining_bytes_divided_by_2;

	remaining_bytes_divided_by_2 = (format4->length - (i - i_starting_value))
		/ 2;
	j = -1;
	while (++j < remaining_bytes_divided_by_2)
		if (read_uint16_move(file, &i, format4->glyph_id_array + j) < 0)
			return (-1);
	return (0);
}
