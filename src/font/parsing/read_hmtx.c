/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_hmtx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:36:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/04 02:36:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "font/ttf_parser.h"

static int	allocate_hmtx(t_ttf *ttf, size_t left_side_bearing_size);
static int	read_hmtx_error(t_ttf *ttf);

int	read_hmtx(const t_string *file, t_ttf *ttf)
{
	const int64_t	head_offset = ttf_get_table_offset(ttf, "hmtx");
	size_t			i;
	size_t			j;
	const size_t	left_side_bearing_size = ttf->maxp.num_glyphs
		- ttf->hhea.num_of_long_hor_metrics;

	if (head_offset < 0)
		return (-1);
	if (allocate_hmtx(ttf, left_side_bearing_size) < 0)
		return (-1);
	i = head_offset;
	j = -1;
	while (++j < ttf->hhea.num_of_long_hor_metrics)
		if (read_uint16_move(file, &i, &ttf->hmtx.h_metrics[j].advance_width)
			|| read_int16_move(file, &i,
				&ttf->hmtx.h_metrics[j].left_side_bearing) < 0)
			return (read_hmtx_error(ttf));
	j = -1;
	while (++j < left_side_bearing_size)
		if (read_int16_move(file, &i, ttf->hmtx.left_side_bearing + j) < 0)
			return (read_hmtx_error(ttf));
	return (0);
}

static int	allocate_hmtx(t_ttf *ttf, const size_t left_side_bearing_size)
{
	ttf->hmtx.h_metrics = malloc(sizeof(*ttf->hmtx.h_metrics)
			* ttf->hhea.num_of_long_hor_metrics);
	ttf->hmtx.left_side_bearing = malloc(sizeof(*ttf->hmtx.left_side_bearing)
			* left_side_bearing_size);
	if (ttf->hmtx.h_metrics == NULL || ttf->hmtx.left_side_bearing == NULL)
		return (read_hmtx_error(ttf));
	return (0);
}

static int	read_hmtx_error(t_ttf *ttf)
{
	free(ttf->hmtx.h_metrics);
	free(ttf->hmtx.left_side_bearing);
	ft_bzero(&ttf->hmtx, sizeof(ttf->hmtx));
	return (-1);
}
