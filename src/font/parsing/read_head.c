/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:42:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 14:59:09 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "font/ttf_parser.h"

#define HEAD_MAGIC_NUMBER_EXPECTED_VALUE 0x5F0F3CF5

static int	read_head_content(const t_string *file, t_ttf *ttf,
				size_t head_offset);

int	read_head(const t_string *file, t_ttf *ttf)
{
	const int64_t	head_offset = ttf_get_table_offset(ttf, "head");

	if (head_offset < 0)
		return (-1);
	return (read_head_content(file, ttf, head_offset));
}

static int	read_head_content(const t_string *file, t_ttf *ttf,
				size_t head_offset)
{
	if (read_uint32_move(file, &head_offset, &ttf->head.version) < 0
		|| read_uint32_move(file, &head_offset, &ttf->head.font_revision) < 0
		|| read_uint32_move(file, &head_offset, &ttf->head.check_sum_adjustment)
		< 0 || read_uint32_move(file, &head_offset, &ttf->head.magic_number) < 0
		|| ttf->head.magic_number != HEAD_MAGIC_NUMBER_EXPECTED_VALUE
		|| read_uint16_move(file, &head_offset, &ttf->head.flags) < 0
		|| read_uint16_move(file, &head_offset, &ttf->head.units_per_em) < 0
		|| read_int64_move(file, &head_offset, &ttf->head.created) < 0
		|| read_int64_move(file, &head_offset, &ttf->head.modified) < 0
		|| read_int16_move(file, &head_offset, &ttf->head.x_min) < 0
		|| read_int16_move(file, &head_offset, &ttf->head.y_min) < 0
		|| read_int16_move(file, &head_offset, &ttf->head.x_max) < 0
		|| read_int16_move(file, &head_offset, &ttf->head.y_max) < 0
		|| read_uint16_move(file, &head_offset, &ttf->head.mac_style) < 0
		|| read_uint16_move(file, &head_offset, &ttf->head.lowest_eec_ppem) < 0
		|| read_int16_move(file, &head_offset, &ttf->head.font_direction_hint)
		< 0 || read_int16_move(file, &head_offset, \
		&ttf->head.index_to_loc_format) < 0 || (ttf->head.index_to_loc_format \
		!= 0 && ttf->head.index_to_loc_format != 1) || read_int16_move(file, \
		&head_offset, &ttf->head.glyph_data_format) < 0)
		return (-1);
	return (0);
}
