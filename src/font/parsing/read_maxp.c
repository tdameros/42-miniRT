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
	if (read_uint32_move(file, &i, &ttf->maxp.version) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.num_glyphs) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_points) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_contours) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_component_points) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_component_contours) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_zones) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_twilight_points) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_storage) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_function_defs) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_instruction_defs) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_stack_elements) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_size_of_instructions) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_component_elements) < 0
		|| read_uint16_move(file, &i, &ttf->maxp.max_component_depth) < 0)
		return (-1);
	return (0);
}
