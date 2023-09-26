/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_max_resolution_reduction.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:37:15 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:37:16 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "font/render.h"
#include "gui/box.h"
#include "gui/optional_boxes.h"
#include "events.h"
#include "gui/utils.h"

static void	minus_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);
static void	plus_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);
static void	center_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);
static void	description_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

void	init_max_resolution_reduction_box(t_engine *engine, t_gui_box *gui_box,
			int *y, t_gui_box *parent)
{
	add_plus_minus_box(engine, gui_box, y, parent);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[0].image, "Max resolution reduction");
	gui_box->children.data[0].on_click = &description_on_click;
	gui_box->children.data[1].children.data[0].on_click = &minus_on_click;
	gui_box->children.data[1].children.data[1].on_click = &center_on_click;
	gui_box->children.data[1].children.data[2].on_click = &plus_on_click;
	update_float_input_box(engine, engine->quality.max_reduction - 1,
		gui_box->children.data + 1);
}

static void	minus_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	if (click_data.button != BUTTON_LEFT)
		return (center_on_click(self, engine, click_data));
	if (engine->quality.max_reduction <= 1
		|| engine->quality.max_reduction == engine->quality.min_reduction)
		return ;
	engine->quality.max_reduction -= 1;
	update_float_input_box(engine, engine->quality.max_reduction - 1,
		self->parent);
}

static void	plus_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	if (click_data.button != BUTTON_LEFT)
		return (center_on_click(self, engine, click_data));
	engine->quality.max_reduction += 1;
	update_float_input_box(engine, engine->quality.max_reduction - 1,
		self->parent);
}

static void	center_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	if (click_data.button == SCROLL_UP)
	{
		click_data.button = BUTTON_LEFT;
		return (plus_on_click(self, engine, click_data));
	}
	if (click_data.button == SCROLL_DOWN)
	{
		click_data.button = BUTTON_LEFT;
		return (minus_on_click(self, engine, click_data));
	}
}

static void	description_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	if (click_data.button == SCROLL_UP)
	{
		click_data.button = BUTTON_LEFT;
		return (plus_on_click(self->parent->children.data[1].children.data + 2,
				engine, click_data));
	}
	if (click_data.button == SCROLL_DOWN)
	{
		click_data.button = BUTTON_LEFT;
		return (minus_on_click(self->parent->children.data[1].children.data + 0,
				engine, click_data));
	}
}
