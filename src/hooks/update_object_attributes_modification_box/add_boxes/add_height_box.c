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
#include "events.h"
#include "gui/object_modification_box.h"

static int	init_height_box_children(t_engine *engine, t_gui_box *gui_box);
static void	height_input_box_on_click_plus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
static void	height_input_box_on_click_minus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
static void	height_input_box_on_click_text(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);

int	add_height_box(t_engine *engine, t_gui_box *gui_box, int *i,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent, \
		(t_vector2i){\
				.x = 0, \
				.y = *i}, \
		(t_vector2i){\
				.x = parent->size.x, \
				.y = parent->size.y * (OBJECT_ATTRIBUTE_BOX_NORMAL_BOX_SIZE \
						/ OBJECT_ATTRIBUTE_BOX_TOTAL_SIZE) \
					- OBJECT_ATTRIBUTE_BOX_OFFSET}, \
		true});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	*i += gui_box->size.y + OBJECT_ATTRIBUTE_BOX_OFFSET;
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
		.text_box = &height_input_box_on_click_text,
		.minus = &height_input_box_on_click_minus};

	if (create_horizontal_boxes(engine, gui_box, "65 35", 0) < 0)
		return (-1);
	if (create_float_input_box(engine, gui_box->children.data + 1, on_click)
		< 0)
	{
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	engine->gui.float_input_boxes.height = gui_box->children.data + 1;
	if (init_image(&gui_box->children.data[0].image, &engine->window,
			gui_box->children.data[0].size.x, gui_box->children.data[0].size.y)
		< 0)
	{
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	change_image_color(&gui_box->children.data[0].image, COLOR_TRANSPARENT);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[0].image, "Height");
	return (0);
}

static void	height_input_box_on_click_plus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data)
{
	t_object	*object;

	object = engine->gui.selected_object.object;
	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (height_input_box_on_click_text(self, engine, click_data));
	if (object == NULL)
		return ;
	object_set_height(object,
		object->height + engine->gui.object_modification_amount);
	engine->scene_changed = true;
	update_float_input_box(engine, object->height,
		engine->gui.float_input_boxes.height);
}

static void	height_input_box_on_click_minus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data)
{
	t_object	*object;

	object = engine->gui.selected_object.object;
	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (height_input_box_on_click_text(self, engine, click_data));
	if (object == NULL
		|| object->height \
			- engine->gui.object_modification_amount <= 0.01)
		return ;
	object_set_height(object,
		object->height - engine->gui.object_modification_amount);
	engine->scene_changed = true;
	update_float_input_box(engine, object->height,
		engine->gui.float_input_boxes.height);
}

static void	height_input_box_on_click_text(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data)
{
	if (click_data.button == SCROLL_UP)
	{
		click_data.button = BUTTON_LEFT;
		return (height_input_box_on_click_plus(self, engine, click_data));
	}
	if (click_data.button == SCROLL_DOWN)
	{
		click_data.button = BUTTON_LEFT;
		return (height_input_box_on_click_minus(self, engine, click_data));
	}
}
