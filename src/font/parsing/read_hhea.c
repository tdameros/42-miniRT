/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_hhea.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:07:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/04 02:07:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "font/ttf_parser.h"

int	read_hhea(const t_string *file, t_ttf *ttf)
{
	const int64_t	head_offset = ttf_get_table_offset(ttf, "hhea");
	size_t			i;
	int16_t			tmp;

	if (head_offset < 0)
		return (-1);
	i = head_offset;
	if (read_uint32_move(file, &i, &ttf->hhea.version) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->hhea.ascent) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->hhea.descent) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->hhea.lineGap) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->hhea.advanceWidthMax) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->hhea.minLeftSideBearing) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->hhea.minRightSideBearing) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->hhea.xMaxExtent) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->hhea.caretSlopeRise) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->hhea.caretSlopeRun) < 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->hhea.caretOffset) < 0)
		return (-1);
	if (read_int16_move(file, &i, &tmp) < 0 || tmp != 0)
		return (-1);
	if (read_int16_move(file, &i, &tmp) < 0 || tmp != 0)
		return (-1);
	if (read_int16_move(file, &i, &tmp) < 0 || tmp != 0)
		return (-1);
	if (read_int16_move(file, &i, &tmp) < 0 || tmp != 0)
		return (-1);
	if (read_int16_move(file, &i, &ttf->hhea.metricDataFormat) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->hhea.numOfLongHorMetrics) < 0)
		return (-1);
	return (0);
}