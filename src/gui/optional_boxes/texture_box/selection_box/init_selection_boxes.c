/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_selection_boxes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:42:25 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 18:42:26 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/optional_boxes.h"


void	init_selection_boxes(t_engine *engine, t_gui_box *gui_box)
{
	init_image(&gui_box->image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	gui_box->draw = &textures_and_normal_maps_draw;
	gui_box->on_click = &textures_and_normal_maps_on_click;
//	gui_box->scroll = TEXTURE_BOX_PPM_OFFSET;
	engine->gui.color_and_material.textures_and_normal_maps.selection_box
		= gui_box;
	load_textures_and_normal_maps(engine);
}
