/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long_hor_metric.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:27:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/04 17:27:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "font/ttf_parser.h"

t_long_hor_metric	get_long_hor_metric(const uint16_t code_point,
						const t_ttf *ttf)
{
	const uint32_t	glyph_index = get_glyph_index(code_point, ttf);

	if (glyph_index < ttf->hhea.num_of_long_hor_metrics)
		return (ttf->hmtx.h_metrics[glyph_index]);
	return ((t_long_hor_metric){
		ttf->hmtx.h_metrics[ttf->hhea.num_of_long_hor_metrics
			- 1].advance_width,
		ttf->hmtx.left_side_bearing[glyph_index
			- ttf->hhea.num_of_long_hor_metrics]
	});
}
