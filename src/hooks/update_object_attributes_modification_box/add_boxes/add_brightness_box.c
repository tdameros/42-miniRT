/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_brightness_box.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:48:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/03 00:48:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <math.h>

#include "gui/box.h"
#include "gui/UI.h"
#include "gui/utils.h"
#include "font/render.h"
#include "events.h"
#include "gui/object_modification_box.h"
#include "hooks.h"

static int	init_brightness_box_children(t_engine *engine, t_gui_box *gui_box);
static void	brightness_input_box_on_click_plus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
static void	brightness_input_box_on_click_minus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
static void	brightness_input_box_on_click_text(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);

int	add_brightness_box(t_engine *engine, t_gui_box *gui_box, int *i,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent, \
		(t_vector2i){\
				.x = 0, \
				.y = *i}, \
		(t_vector2i){\
				.x = parent->size.x, \
				.y = get_normal_box_size(parent)}, \
		true});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	*i += gui_box->size.y + OBJECT_ATTRIBUTE_BOX_OFFSET;
	if (init_brightness_box_children(engine, gui_box) < 0)
	{
		destroy_t_image(&engine->window, &gui_box->image);
		ft_bzero(gui_box, sizeof(*gui_box));
		return (-1);
	}
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	return (0);
}

static int	init_brightness_box_children(t_engine *engine, t_gui_box *gui_box)
{
	const t_float_input_box_on_click	on_click = {
		.plus = &brightness_input_box_on_click_plus,
		.text_box = &brightness_input_box_on_click_text,
		.minus = &brightness_input_box_on_click_minus};

	if (create_horizontal_boxes(engine, gui_box, "65 35", 0) < 0)
		return (-1);
	if (create_float_input_box(engine, gui_box->children.data + 1, on_click)
		< 0)
	{
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	engine->gui.float_input_boxes.brightness
		= gui_box->children.data + 1;
	if (init_image(&gui_box->children.data[0].image, &engine->window,
			gui_box->children.data[0].size.x, gui_box->children.data[0].size.y)
		< 0)
	{
		destroy_t_gui_box(&engine->window, gui_box);
		return (-1);
	}
	change_image_color(&gui_box->children.data[0].image, COLOR_TRANSPARENT);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[0].image, "Brightness");
	return (0);
}

static void	brightness_input_box_on_click_plus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data)
{
	t_light	*light;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (brightness_input_box_on_click_text(self, engine, click_data));
	light = engine->gui.selected_object.light;
	if (light == NULL)
		return ;
	light_set_brightness(light, fminf(light->brightness + 0.01, 1.f));
	engine->scene_changed = true;
	update_float_input_box(engine, light->brightness,
		engine->gui.float_input_boxes.brightness);
}

static void	brightness_input_box_on_click_minus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data)
{
	t_light	*light;

	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return (brightness_input_box_on_click_text(self, engine, click_data));
	light = engine->gui.selected_object.light;
	if (light == NULL)
		return ;
	light_set_brightness(light, fmaxf(light->brightness - 0.01, 0.f));
	engine->scene_changed = true;
	update_float_input_box(engine, light->brightness,
		engine->gui.float_input_boxes.brightness);
}

static void	brightness_input_box_on_click_text(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data)
{
	if (click_data.button == SCROLL_UP)
	{
		click_data.button = BUTTON_LEFT;
		return (brightness_input_box_on_click_plus(self, engine, click_data));
	}
	if (click_data.button == SCROLL_DOWN)
	{
		click_data.button = BUTTON_LEFT;
		return (brightness_input_box_on_click_minus(self, engine, click_data));
	}
}
