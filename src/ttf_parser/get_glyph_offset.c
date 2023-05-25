/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_glyph_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:41:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/15 14:41:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "ttf.h"

static int		get_index(uint16_t code_point, const t_format4 *format4);

uint32_t	get_glyph_offset(const uint32_t glyph_index, const t_ttf *ttf)
{
	return (ttf->loca.offsets[(glyph_index < ttf->loca.size) * glyph_index]);
}

uint32_t	get_glyph_index(const uint16_t code_point, const t_ttf *ttf)
{
	const t_format4	*format4 = ttf->format4;
	const int		index = get_index(code_point, format4);
	uint16_t		*ptr;

	if (index == -1)
		return (0);
	if (format4->startCode[index] < code_point)
	{
		if (format4->idRangeOffset[index] == 0)
			return (code_point + format4->idDelta[index]);
		ptr = format4->idRangeOffset + index + format4->idRangeOffset[index]
			/ 2;
		ptr += code_point - format4->startCode[index];
		if (*ptr == 0)
			return (0);
		return (*ptr + format4->idDelta[index]);
	}
	return (0);
}

static int	get_index(const uint16_t code_point, const t_format4 *format4)
{
	uint16_t		i;
	const uint16_t	i_limit = format4->segCountX2 / 2;

	i = -1;
	while (++i < i_limit)
	{
		if (format4->endCode[i] > code_point)
			return (i);
	}
	return (-1);
}
