/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:42:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/19 19:42:00 by vfries           ###   ########lyon.fr   */
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
		|| read_uint32_move(file, &head_offset, &ttf->head.fontRevision) < 0
		|| read_uint32_move(file, &head_offset,
			&ttf->head.checkSumAdjustment) < 0
		|| read_uint32_move(file, &head_offset, &ttf->head.magicNumber) < 0
		|| ttf->head.magicNumber != HEAD_MAGIC_NUMBER_EXPECTED_VALUE
		|| read_uint16_move(file, &head_offset, &ttf->head.flags) < 0
		|| read_uint16_move(file, &head_offset, &ttf->head.unitsPerEm) < 0
		|| read_int64_move(file, &head_offset, &ttf->head.created) < 0
		|| read_int64_move(file, &head_offset, &ttf->head.modified) < 0
		|| read_int16_move(file, &head_offset, &ttf->head.xMin) < 0
		|| read_int16_move(file, &head_offset, &ttf->head.yMin) < 0
		|| read_int16_move(file, &head_offset, &ttf->head.xMax) < 0
		|| read_int16_move(file, &head_offset, &ttf->head.yMax) < 0
		|| read_uint16_move(file, &head_offset, &ttf->head.macStyle) < 0
		|| read_uint16_move(file, &head_offset, &ttf->head.lowestRecPPEM) < 0
		|| read_int16_move(file, &head_offset, &ttf->head.fontDirectionHint) < 0
		|| read_int16_move(file, &head_offset, &ttf->head.indexToLocFormat) < 0
		|| (ttf->head.indexToLocFormat != 0 && ttf->head.indexToLocFormat != 1)
		|| read_int16_move(file, &head_offset, &ttf->head.glyphDataFormat) < 0)
		return (-1);
	return (0);
}
