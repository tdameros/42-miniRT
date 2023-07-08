/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf_get_table_offset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:40:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/19 17:40:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "font/ttf_parser.h"

///
/// @param ttf font_directory needs to have been parsed successfully to call
/// this function (will seg fault otherwise)
/// @param table_name needs to be a 4 char string (excluding \0 which is not
/// necessary) or will overflow
/// @return
int64_t	ttf_get_table_offset(const t_ttf *ttf, const char table_name[5])
{
	const uint32_t	table_tag = read_uint32_unsafe(table_name);
	uint16_t		i;

	i = ttf->font_directory.offset_subtable.num_tables;
	while (i--)
		if (ttf->font_directory.table_directory[i].tag == table_tag)
			return (ttf->font_directory.table_directory[i].offset);
	return (-1);
}
