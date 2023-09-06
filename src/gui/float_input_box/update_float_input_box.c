/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_float_input_box.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:07:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/29 18:07:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "engine.h"
#include "gui/box.h"
#include "font/render.h"
#include "gui/utils.h"

#define SPRINTF_PARAM "%.2f"

void	update_float_input_box(const t_engine *engine, const float f,
			t_gui_box *input_box)
{
	size_t	size;
	char	*buffer;

	if (input_box == NULL)
		return ;
	draw_center_box_image(&input_box->children.data[1].image);
	size = snprintf(NULL, 0, SPRINTF_PARAM, f) + 1;
	buffer = malloc(size);
	if (buffer == NULL)
		return (write_centered_string_to_image(&engine->gui.font,
				&input_box->children.data[1].image, "ENOMEM"));
	snprintf(buffer, size, SPRINTF_PARAM, f);
	write_centered_number_to_image(&engine->gui.font,
		&input_box->children.data[1].image, buffer);
	free(buffer);
}
