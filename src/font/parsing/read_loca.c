/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_loca.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:16:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/21 21:16:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "font/ttf_parser.h"

static int	read_loca_offsets(const t_string *file, t_loca *loca,
				size_t offset, bool is_short);

int	read_loca(const t_string *file, t_ttf *ttf)
{
	const int64_t	loca_offset = ttf_get_table_offset(ttf, "loca");

	if (loca_offset < 0)
		return (-1);
	ft_bzero(&ttf->loca, sizeof(ttf->loca));
	ttf->loca.size = ttf->maxp.numGlyphs;
	return (read_loca_offsets(file, &ttf->loca, loca_offset,
			ttf->head.indexToLocFormat == 0));
}

static int	read_loca_offsets(const t_string *file, t_loca *loca,
				size_t offset, const bool is_short)
{
	size_t		i;
	uint16_t	tmp;

	loca->offsets = ft_calloc(loca->size,
			sizeof(*loca->offsets));
	if (loca->offsets == NULL)
		return (-1);
	i = -1;
	while (++i < loca->size)
	{
		if (is_short)
		{
			if (read_uint16_move(file, &offset, &tmp) < 0)
				return (-1);
			loca->offsets[i] = tmp * 2;
		}
		else if (read_uint32_move(file, &offset, loca->offsets + i) < 0)
			return (-1);
	}
	return (0);
}
