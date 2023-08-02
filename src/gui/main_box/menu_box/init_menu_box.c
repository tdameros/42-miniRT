/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_box.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:23:12 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 17:23:13 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "gui/box.h"
#include "gui/main_gui_box.h"
#include "engine.h"
#include "colors.h"
#include "gui/UI.h"
#include "gui/utils.h"

static void	init_menu_gui_box_children(t_engine *engine, t_gui_box *gui_box);
static void	init_saving_icon_box(t_engine *engine, t_gui_box *gui_box);
static void	init_menu_settings_icon_box(t_engine *engine, t_gui_box *gui_box);

void	init_menu_gui_box(t_engine *engine, t_gui_box *gui_box,
			t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){NULL, \
		(t_vector2i){
			.x = parent->size.x - parent->size.x / 4, \
			.y = 8}, \
		(t_vector2i){
			.x = parent->size.x / 4 - 8, \
			.y = parent->size.y - 16}, true});
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	init_menu_gui_box_children(engine, gui_box);
}

static void	init_menu_gui_box_children(t_engine *engine, t_gui_box *gui_box)
{
	create_n_horizontal_boxes(engine, gui_box, 2, (t_vector2i){4, 4});
	init_saving_icon_box(engine, gui_box->children.data + 0);
	init_menu_settings_icon_box(engine, gui_box->children.data + 1);
}

static void	init_saving_icon_box(t_engine *engine, t_gui_box *gui_box)
{
	init_image(&gui_box->image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	change_image_color(&gui_box->on_hover_image, HOVER_GUI_COLOR);
	round_image_corners(&gui_box->on_hover_image, BOX_ROUNDING_RADIUS);
}

static void	init_menu_settings_icon_box(t_engine *engine, t_gui_box *gui_box)
{
	init_image(&gui_box->image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	init_settings_icon(gui_box);
}
