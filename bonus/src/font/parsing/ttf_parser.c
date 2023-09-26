/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 03:26:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/12 03:26:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "font/ttf_parser.h"

#include <stdio.h>

static int	parse_ttf_file(t_ttf *ttf, t_string *file);
static int	error_in_ttf_parser(t_string *file, t_ttf *ttf);
static int	read_secondary_tables(t_ttf *ttf, t_string *file);

int	ttf_parser(t_ttf *ttf, char *file_name)
{
	t_string	file;
	int			result;

	file = ft_read_file(file_name);
	if (file.data == NULL)
	{
		perror("ttf_parser failed");
		return (-1);
	}
	ft_bzero(ttf, sizeof(*ttf));
	result = parse_ttf_file(ttf, &file);
	free(file.data);
	return (result);
}

void	destroy_t_ttf(t_ttf *ttf)
{
	free(ttf->font_directory.table_directory);
	free(ttf->cmap.subtables);
	free(ttf->format4);
	free(ttf->loca.offsets);
	free(ttf->hmtx.h_metrics);
	free(ttf->hmtx.left_side_bearing);
	while (ttf->glyphs_count--)
	{
		free(ttf->glyphs[ttf->glyphs_count].end_pts_of_contours);
		free(ttf->glyphs[ttf->glyphs_count].instructions);
		free(ttf->glyphs[ttf->glyphs_count].flags);
		free(ttf->glyphs[ttf->glyphs_count].x_coordinates);
		free(ttf->glyphs[ttf->glyphs_count].y_coordinates);
	}
	free(ttf->glyphs);
}

static int	parse_ttf_file(t_ttf *ttf, t_string *file)
{
	if (read_font_directory(file, &ttf->font_directory) < 0)
		return (ft_print_error("Failed to parse font directory\n"),
			error_in_ttf_parser(file, ttf));
	if (read_cmap(file, ttf) < 0)
		return (ft_print_error("Failed to read cmap()\n"),
			error_in_ttf_parser(file, ttf));
	if (read_format4(file, ttf) < 0)
		return (ft_print_error("Failed to read format4\n"),
			error_in_ttf_parser(file, ttf));
	if (read_secondary_tables(ttf, file) < 0)
		return (-1);
	ttf->glyphs = get_glyph_outlines(file, ttf);
	if (ttf->glyphs == NULL)
		return (error_in_ttf_parser(file, ttf));
	ttf->glyphs_count = ttf->maxp.num_glyphs;
	return (0);
}

static int	error_in_ttf_parser(t_string *file, t_ttf *ttf)
{
	free(file->data);
	destroy_t_ttf(ttf);
	return (-1);
}

static int	read_secondary_tables(t_ttf *ttf, t_string *file)
{
	if (read_head(file, ttf) < 0)
		return (ft_print_error("Failed to read head\n"),
			error_in_ttf_parser(file, ttf));
	if (read_maxp(file, ttf) < 0)
		return (ft_print_error("Failed to read maxp\n"),
			error_in_ttf_parser(file, ttf));
	if (read_loca(file, ttf) < 0)
		return (ft_print_error("Failed to read loca\n"),
			error_in_ttf_parser(file, ttf));
	if (read_hhea(file, ttf) < 0)
		return (ft_print_error("Failed to read hhea\n"),
			error_in_ttf_parser(file, ttf));
	if (read_hmtx(file, ttf) < 0)
		return (ft_print_error("Failed to read hmtx\n"),
			error_in_ttf_parser(file, ttf));
	return (0);
}
