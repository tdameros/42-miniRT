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

#include "ttf.h"

#define HEAD_MAGIC_NUMBER_EXPECTED_VALUE 0x5F0F3CF5

int	read_head(const t_string *file, t_ttf *ttf)
{
	const int64_t	head_offset = ttf_get_table_offset(ttf, "head");
	size_t			i;

	if (head_offset < 0)
		return (-1);
	i = head_offset;
	if (read_int32_move(file, &i, &ttf->head.version) < 0)
		return (-1);
	if (read_int32_move(file, &i, &ttf->head.fontRevision) < 0)
		return (-1);
	if (read_uint32_move(file, &i, &ttf->head.checkSumAdjustment) < 0)
		return (-1);
	if (read_uint32_move(file, &i, &ttf->head.magicNumber) < 0
		|| ttf->head.magicNumber != HEAD_MAGIC_NUMBER_EXPECTED_VALUE)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->head.flags) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->head.unitsPerEm) < 0)
		return (-1);
	if (read_int64_move(file, &i, &ttf->head.created) < 0)
		return (-1);
	if (read_int64_move(file, &i, &ttf->head.modified) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->head.xMin) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->head.yMin) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->head.xMax) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->head.yMax) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->head.macStyle) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->head.lowestRecPPEM) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->head.fontDirectionHint) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->head.indexToLocFormat) < 0
		|| (ttf->head.indexToLocFormat != 0 && ttf->head.indexToLocFormat != 1))
		return (-1);
	if (read_int16_move(file, &i, &ttf->head.glyphDataFormat) < 0)
		return (-1);
	return (0);
}
