/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main_box.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:27:20 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 17:27:20 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <stdlib.h>

#include "gui/box.h"
#include "colors.h"
#include "gui/main_gui_box.h"
#include "gui/UI.h"

static void	init_main_gui_box_children(t_engine *engine, t_gui_box *gui_box);

void	init_main_gui_box(t_engine *engine, t_gui_box *gui_box)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){NULL,
			(t_vector2i){.x = 12, \
						.y = 12},
			(t_vector2i){.x = engine->window.size.x - 24, \
						.y = engine->window.size.y / 8}, true});
	change_image_color(&gui_box->image, BASE_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	init_main_gui_box_children(engine, gui_box);
}

static void	init_main_gui_box_children(t_engine *engine, t_gui_box *gui_box)

{
	gui_box->children.size = 2;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
			* gui_box->children.size);
	if (gui_box->children.data == NULL)
		ft_fatal_error("init_main_gui_box_children: malloc failed");
	init_object_creation_gui_box(engine, gui_box->children.data, gui_box);
	init_menu_gui_box(engine, gui_box->children.data + 1, gui_box);
}
