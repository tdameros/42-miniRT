/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_glyph_outlines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:40:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/24 19:40:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ttf.h"

static void	destroy_glyph_outlines_on_read_failure(t_glyph_outline *outlines,
				size_t size);

t_glyph_outline	*get_glyph_outlines(const t_string *file, t_ttf *ttf)
{
	const int64_t	glyph_table_offset = ttf_get_table_offset(ttf, "glyf");
	t_glyph_outline	*glyph_outlines;
	size_t			i;

	if (glyph_table_offset < 0)
		return (ft_print_error("glyf table not found\n"), \
				NULL);
	glyph_outlines = malloc(sizeof(*glyph_outlines) * ttf->loca.size);
	if (glyph_outlines == NULL)
		return (ft_print_error("Failed to malloc glyph_outlines\n"), \
				NULL);
	i = -1;
	while (++i < ttf->loca.size)
	{
		if (read_glyph_outline(file, glyph_table_offset
				+ get_glyph_offset(i, ttf), glyph_outlines + i) < 0)
		{
			ft_print_error("Failed to read glyph table\n");
			destroy_glyph_outlines_on_read_failure(glyph_outlines, i);
			return (NULL);
		}
	}
	return (glyph_outlines);
}

static void	destroy_glyph_outlines_on_read_failure(t_glyph_outline *outlines,
				size_t size)
{
	while (size--)
	{
		free(outlines[size].endPtsOfContours);
		free(outlines[size].instructions);
		free(outlines[size].flags);
		free(outlines[size].xCoordinates);
		free(outlines[size].yCoordinates);
	}
	free(outlines);
}
