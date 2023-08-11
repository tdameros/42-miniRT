/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_toggle_box.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 22:34:00 by vfries            #+#    #+#             */
/*   Updated: 2023/08/02 19:32:00 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "engine.h"
#include "gui/box.h"
#include "gui/object_modification_box.h"
#include "hooks.h"
#include "gui/UI.h"
#include "colors.h"

#define OFFSET 4

static void	init_toggle_box_children(t_engine *engine, t_gui_box *gui_box);
static void	init_toggle_box_button(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent, int button_size);
static void	init_toggle_box_text_box(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent, int button_size);

void	add_toggle_box(t_engine *engine, t_gui_box *gui_box, int *y,
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
	init_toggle_box_children(engine, gui_box);
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
}

static void	init_toggle_box_children(t_engine *engine, t_gui_box *gui_box)
{
	int	button_size;

	gui_box->children.size = 2;
	gui_box->children.data = ft_calloc(gui_box->children.size,
			sizeof(*gui_box->children.data));
	if (gui_box->children.data == NULL)
		ft_fatal_error("init_toggle_box_children: malloc error");
	button_size = fminf(gui_box->size.x - OFFSET * 2, \
						gui_box->size.y - OFFSET * 2);
	init_toggle_box_button(engine, gui_box->children.data, gui_box,
		button_size);
	init_toggle_box_text_box(engine, gui_box->children.data + 1, gui_box,
		button_size);
}

static void	init_toggle_box_button(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent, const int button_size)
{
	const t_vector2i	position = {.x = OFFSET, .y = OFFSET};
	const t_vector2i	size = {.x = button_size, .y = button_size};

	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent,
			position, size, true});
	init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
		gui_box->size.y);
}

static void	init_toggle_box_text_box(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent, const int button_size)
{
	const t_vector2i	position = {.x = button_size + OFFSET * 2, .y = 0};
	const t_vector2i	size = {
		.x = parent->size.x - (button_size + OFFSET * 3),
		.y = parent->size.y};

	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent,
			position, size, true});
}
