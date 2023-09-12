/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_button_box.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:48:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/03 00:48:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "gui/box.h"
#include "gui/UI.h"
#include "gui/object_modification_box.h"
#include "hooks.h"

void	add_button_box(t_engine *engine, t_gui_box *gui_box, int *y,
			t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent, \
		(t_vector2i){
			.x = 0,
			.y = *y}, \
		(t_vector2i){
			.x = parent->size.x,
			.y = get_normal_box_size(\
					engine->gui.object_attributes_modification_box)}, \
		true});
	*y += gui_box->size.y + OBJECT_ATTRIBUTE_BOX_OFFSET;
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	change_image_color(&gui_box->on_hover_image, HOVER_GUI_COLOR);
	round_image_corners(&gui_box->on_hover_image, BOX_ROUNDING_RADIUS);
}
