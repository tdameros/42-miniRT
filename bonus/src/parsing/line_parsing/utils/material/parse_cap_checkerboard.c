/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cap_checkerboard.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:05:30 by vfries            #+#    #+#             */
/*   Updated: 2023/09/03 11:05:31 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "parsing.h"

void	parse_cap_checkerboard(t_object *object, char *raw_checkerboard_data)
{
	const t_checkerboard_parsing_data	checkerboard_data
		= get_checkerboard_parsing_data(raw_checkerboard_data);

	free_cap_texture(&object->material);
	if (checkerboard_data.size.x + checkerboard_data.size.y < .01f)
		return ;
	set_cap_checkerboard(&object->material, checkerboard_data.size,
		vector3f_divide(checkerboard_data.color, 255.f));
}
