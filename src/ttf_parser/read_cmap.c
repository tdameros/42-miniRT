/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:21:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/12 14:21:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "ttf.h"

static int	read_cmap_encoding_subtable(const t_string *file, t_ttf *ttf,
				size_t i);
static int	error_read_cmap_encoding_subtable(t_cmap *cmap);
static bool	get_format4_offset(t_ttf *ttf);

int	read_cmap(const t_string *file, t_ttf *ttf)
{
	const int64_t	cmap_offset = ttf_get_table_offset(ttf, "cmap");
	size_t			i;

	if (cmap_offset < 0)
		return (-1);
	ttf->cmap_offset = cmap_offset;
	i = cmap_offset;
	if (read_uint16_move(file, &i, &ttf->cmap.version) < 0)
		return (-1);
	if (read_uint16_move(file, &i, &ttf->cmap.number_subtables) < 0)
		return (-1);
	return (read_cmap_encoding_subtable(file, ttf, i));
}

static int	read_cmap_encoding_subtable(const t_string *file, t_ttf *ttf,
				size_t i)
{
	size_t						j;
	t_cmap_encoding_subtable	*current_subtable;

	ttf->cmap.subtables = ft_calloc(ttf->cmap.number_subtables,
			sizeof(*ttf->cmap.subtables));
	if (ttf->cmap.subtables == NULL)
		return (-1);
	j = -1;
	while (++j < ttf->cmap.number_subtables)
	{
		current_subtable = ttf->cmap.subtables + j;
		if (read_uint16_move(file, &i, &current_subtable->platform_id) < 0)
			return (error_read_cmap_encoding_subtable(&ttf->cmap));
		if (read_uint16_move(file, &i, &current_subtable->platform_specific_id)
			< 0)
			return (error_read_cmap_encoding_subtable(&ttf->cmap));
		if (read_uint32_move(file, &i, &current_subtable->offset) < 0)
			return (error_read_cmap_encoding_subtable(&ttf->cmap));
	}
	if (get_format4_offset(ttf))
		return (0);
	free(ttf->cmap.subtables);
	return (-1);
}

static int	error_read_cmap_encoding_subtable(t_cmap *cmap)
{
	free(cmap->subtables);
	cmap->subtables = NULL;
	return (-1);
}

static bool	get_format4_offset(t_ttf *ttf)
{
	uint16_t	i;

	i = ttf->cmap.number_subtables;
	while (i--)
	{
		if (ttf->cmap.subtables[i].platform_id == 0
			&& ttf->cmap.subtables[i].platform_specific_id == 3)
		{
			ttf->format4_offset = ttf->cmap.subtables[i].offset;
			return (true);
		}
	}
	ft_print_error("Error: font needs to have a unicode cmap with platform "
		"specific id == 3\n");
	return (false);
}
