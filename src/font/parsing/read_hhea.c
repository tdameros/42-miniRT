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

static int	read_hhea_content(const t_string *file, t_ttf *ttf, size_t i);

int	read_hhea(const t_string *file, t_ttf *ttf)
{
	const int64_t	head_offset = ttf_get_table_offset(ttf, "hhea");

	if (head_offset < 0)
		return (-1);
	return (read_hhea_content(file, ttf, head_offset));
}

static int	read_hhea_content(const t_string *file, t_ttf *ttf, size_t i)
{
	int16_t	tmp;

	if (read_uint32_move(file, &i, &ttf->hhea.version) < 0
		|| read_int16_move(file, &i, &ttf->hhea.ascent) < 0
		|| read_int16_move(file, &i, &ttf->hhea.descent) < 0
		|| read_int16_move(file, &i, &ttf->hhea.line_gap) < 0
		|| read_uint16_move(file, &i, &ttf->hhea.advance_width_max) < 0
		|| read_int16_move(file, &i, &ttf->hhea.min_left_side_bearing) < 0
		|| read_int16_move(file, &i, &ttf->hhea.min_right_side_bearing) < 0
		|| read_int16_move(file, &i, &ttf->hhea.x_max_extent) < 0
		|| read_int16_move(file, &i, &ttf->hhea.caret_slope_rise) < 0
		|| read_int16_move(file, &i, &ttf->hhea.caret_slope_run) < 0
		|| read_int16_move(file, &i, &ttf->hhea.caret_offset) < 0
		|| read_int16_move(file, &i, &tmp) < 0 || tmp != 0
		|| read_int16_move(file, &i, &tmp) < 0 || tmp != 0
		|| read_int16_move(file, &i, &tmp) < 0 || tmp != 0
		|| read_int16_move(file, &i, &tmp) < 0 || tmp != 0
		|| read_int16_move(file, &i, &ttf->hhea.metric_data_format) < 0
		|| read_uint16_move(file, &i, &ttf->hhea.num_of_long_hor_metrics) < 0)
		return (-1);
	return (0);
}
