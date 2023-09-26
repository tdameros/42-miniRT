/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:22:14 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 19:15:34 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "engine.h"
#include "gui/box.h"
#include "gui/main_gui_box.h"
#include "window.h"
#include "libft.h"
#include "gui/object_modification_box.h"
#include "gui/object_list_box.h"
#include "gui/optional_boxes.h"

static void	init_boxes(t_engine *engine);
static void	init_message(t_engine *engine);

int	init_gui(t_engine *engine)
{
	engine->gui.gui_boxes.size = 3;
	engine->gui.gui_boxes.data = ft_calloc(engine->gui.gui_boxes.size,
			sizeof(*engine->gui.gui_boxes.data));
	engine->gui.optional_gui_boxes.size = NUMBER_OF_OPTIONAL_BOXES;
	engine->gui.optional_gui_boxes.data = ft_calloc(
			engine->gui.optional_gui_boxes.size,
			sizeof(*engine->gui.optional_gui_boxes.data));
	if (engine->gui.gui_boxes.data == NULL
		|| engine->gui.optional_gui_boxes.data == NULL)
		return (-1);
	engine->gui.current_optional_box = NO_OPTIONAL_BOX;
	engine->gui.draw_gui_image = &put_image_to_image_unsafe;
	engine->gui.object_modification_amount = 0.1f;
	engine->gui.object_rotation_degrees = 10.0f;
	engine->gui.fps.last_update = ft_get_current_time();
	engine->gui.color_and_material.material_to_assign_to_new_objects
		= material_create((t_color){0.f, 0.f, 1.f}, 0.f, 0.f);
	engine->gui.hide_animation.hide_animation_finished = true;
	init_boxes(engine);
	init_message(engine);
	init_image(&engine->gui.screen_shot.image, &engine->window,
		engine->window.size.x, engine->window.size.y);
	return (0);
}

static void	init_boxes(t_engine *engine)
{
	init_main_gui_box(engine, engine->gui.gui_boxes.data);
	init_object_modification_gui_box(engine,
		engine->gui.gui_boxes.data + 1, engine->gui.gui_boxes.data);
	init_object_list_box(engine, engine->gui.gui_boxes.data + 2,
		engine->gui.gui_boxes.data, engine->gui.gui_boxes.data + 1);
	init_settings_box(engine,
		engine->gui.optional_gui_boxes.data + SETTINGS_BOX,
		engine->gui.gui_boxes.data, engine->gui.gui_boxes.data + 2);
	init_texture_box(engine,
		engine->gui.optional_gui_boxes.data + TEXTURE_BOX,
		engine->gui.gui_boxes.data, engine->gui.gui_boxes.data + 2);
	init_add_mesh_object_box(engine,
		engine->gui.optional_gui_boxes.data + MESH_OBJECT_CREATION_BOX,
		engine->gui.gui_boxes.data, engine->gui.gui_boxes.data + 2);
}

static void	init_message(t_engine *engine)
{
	const int	width = engine->ray_traced_image.width;
	const int	height = engine->ray_traced_image.height * 0.05f;

	init_image(&engine->gui.message.image_to_display, &engine->window,
		width, height);
	init_image(&engine->gui.message.image_with_message, &engine->window,
		width, height);
	engine->gui.message.y_position = engine->ray_traced_image.height
		- engine->ray_traced_image.height / 10;
}
