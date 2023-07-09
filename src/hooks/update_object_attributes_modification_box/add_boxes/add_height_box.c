/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_height_box.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:48:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/03 00:48:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "gui/box.h"
#include "gui/UI.h"
#include "gui/utils.h"
#include "font/render.h"

static int	init_height_box_children(t_engine *engine, t_gui_box *gui_box);
static void	height_input_box_on_click_plus(struct s_gui_box *self,
				t_engine *engine, int y, int x);
static void	height_input_box_on_click_minus(struct s_gui_box *self,
				t_engine *engine, int y, int x);

int	add_height_box(t_engine *engine, t_gui_box *gui_box, int *i,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, parent, \
	(t_vector2i){
			.x = 0,
			.y = *i}, \
	(t_vector2i){
			.x = parent->size.x,
			.y = 25});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	*i += gui_box->size.y + 8;
	if (init_height_box_children(engine, gui_box) < 0)
	{
		destroy_t_image(&engine->window, &gui_box->image);
		ft_bzero(gui_box, sizeof(*gui_box));
		return (-1);
	}
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, 10);
	return (0);
}

static int	init_height_box_children(t_engine *engine, t_gui_box *gui_box)
{
	const t_float_input_box_on_click	on_click = {
		.plus = &height_input_box_on_click_plus,
		.minus = &height_input_box_on_click_minus};

	if (create_horizontal_boxes(engine, gui_box, "65 35", 0) < 0)
		return (-1);
	if (create_float_input_box(engine, gui_box->children.data + 1, on_click)
		< 0)
	{
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	change_image_color(&gui_box->children.data[0].image, COLOR_TRANSPARENT);
		write_centered_string_to_image(&engine->gui.font, &gui_box->children.data[0].image,
		"Height");
	return (0);
}

static void	height_input_box_on_click_plus(struct s_gui_box *self,
				t_engine *engine, int y, int x)
{
	t_object	*object;

	object = engine->gui.selected_object;
	(void)self;
	(void)y;
	(void)x;
	if (engine->gui.selected_object == NULL)
		return ;
	object_set_height(object,
		object->height + engine->gui.object_modification_amount);
	engine->scene_changed = true;
}

static void	height_input_box_on_click_minus(struct s_gui_box *self,
				t_engine *engine, int y, int x)
{
	t_object	*object;

	object = engine->gui.selected_object;
	(void)self;
	(void)y;
	(void)x;
	if (object == NULL
		|| object->height \
			- engine->gui.object_modification_amount <= 0.01)
		return ;
	object_set_height(object,
		object->height - engine->gui.object_modification_amount);
	engine->scene_changed = true;
}
