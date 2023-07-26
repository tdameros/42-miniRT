/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_description_box.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:59:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/23 18:59:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "font/render.h"

int	init_description_box(t_engine *engine, t_gui_box *gui_box,
		const char *description)
{
	if (init_image(&gui_box->image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		return (-1);
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	write_centered_string_to_image(&engine->gui.font, &gui_box->image,
		description);
	image_draw_outline(&gui_box->image, 2, COLOR_BLACK);
	return (0);
}
