/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:22:14 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 17:22:15 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "engine.h"
#include "gui/box.h"
#include "gui/main_gui_box.h"
#include "window.h"
#include "libft.h"
#include "gui/object_modification_box.h"
#include "gui/object_list_box.h"
#include "gui/optional_boxes.h"

static void	init_boxes(t_engine *engine);

void	init_gui(t_engine *engine)
{
	engine->gui.gui_boxes.size = 3;
	engine->gui.gui_boxes.data = ft_calloc(engine->gui.gui_boxes.size,
			sizeof(*engine->gui.gui_boxes.data));
	engine->gui.optional_gui_boxes.size = 1;
	engine->gui.optional_gui_boxes.data = ft_calloc(
			engine->gui.optional_gui_boxes.size,
			sizeof(*engine->gui.optional_gui_boxes.data));
	if (engine->gui.gui_boxes.data == NULL
		|| engine->gui.optional_gui_boxes.data == NULL)
		ft_fatal_error("init_gui: malloc failed");
	engine->gui.current_optional_box = NO_OPTIONAL_BOX;
	engine->gui.draw_gui_image = &put_image_to_image_unsafe;
	engine->gui.object_modification_amount = 0.1f;
	engine->gui.object_rotation_degrees = 10.0f;
	engine->gui.fps.last_update = ft_get_current_time();
	engine->gui.color_and_material.material_to_assign_to_new_objects
		= material_create((t_color){0.f, 0.f, 1.f}, 0.f, 0.f);
	init_boxes(engine);
}

static void	init_boxes(t_engine *engine)
{
	init_main_gui_box(engine, engine->gui.gui_boxes.data);
	init_object_modification_gui_box(engine,
		engine->gui.gui_boxes.data + 1, engine->gui.gui_boxes.data);
	init_object_list_box(engine, engine->gui.gui_boxes.data + 2,
		engine->gui.gui_boxes.data, engine->gui.gui_boxes.data + 1);
	init_settings_box(engine, engine->gui.optional_gui_boxes.data,
		engine->gui.gui_boxes.data, engine->gui.gui_boxes.data + 2);
}
