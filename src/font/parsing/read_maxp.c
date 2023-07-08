/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maxp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:47:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/20 18:47:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "font/ttf_parser.h"

int	read_maxp(const t_string *file, t_ttf *ttf)
{
	const int64_t	maxp_offset = ttf_get_table_offset(ttf, "maxp");
	size_t			i;

	if (maxp_offset < 0)
		return (-1);
	i = maxp_offset;
	if (read_uint32_move(file, &i, &ttf->maxp.version) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.numGlyphs) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxPoints) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxContours) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxComponentPoints) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxComponentContours) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxZones) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxTwilightPoints) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxStorage) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxFunctionDefs) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxInstructionDefs) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxStackElements) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxSizeOfInstructions) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxComponentElements) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->maxp.maxComponentDepth) < 0)
		return (-1);
	return (0);
}
