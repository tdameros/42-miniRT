/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_list_box.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:39:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/16 11:39:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "engine.h"
#include "gui/box.h"
#include "gui/UI.h"
#include "gui/utils.h"
#include "gui/object_list_box.h"

void	init_object_list_box(t_engine *engine, t_gui_box *gui_box,
			const t_gui_box *main_gui_box,
			const t_gui_box *object_modification_gui_box)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){NULL,
			(t_vector2i){main_gui_box->position.x, \
						object_modification_gui_box->position.y},
			(t_vector2i){object_modification_gui_box->size.x / 4.f * 3.f, \
						object_modification_gui_box->size.y / 3},
			true});
	engine->gui.object_list_box = gui_box;
	engine->gui.object_list_box->draw = &object_list_gui_box_draw;
	engine->gui.object_list_box->on_click = &object_list_gui_box_on_click;
	engine->gui.object_list_box->scroll = OBJECT_LIST_OFFSET;
	ft_vector_create(&engine->gui.light_boxes, sizeof(t_gui_box), 0);
	ft_vector_create(&engine->gui.object_boxes, sizeof(t_gui_box), 0);
}
