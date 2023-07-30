/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_float_input_box.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:55:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/29 19:31:24 by vincent          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "gui/box.h"
#include "gui/utils.h"
#include "gui/UI.h"

#define LINE_THICKNESS_DIVIDER 11
#define BORDER 4

static void	init_left_box_image(t_engine *engine, t_gui_box *gui_box);
static void	init_center_box_image(t_engine *engine, t_gui_box *gui_box);
static void	init_right_box_image(t_engine *engine, t_gui_box *gui_box);

void	create_float_input_box(t_engine *engine, t_gui_box *gui_box,
			t_float_input_box_on_click on_click)
{
	if (create_horizontal_boxes(engine, gui_box, "20 60 20", 0) < 0)
		ft_fatal_error("Error during float input box creation");
	gui_box->children.data[0].on_click = on_click.minus;
	gui_box->children.data[1].on_click = on_click.text_box;
	gui_box->children.data[2].on_click = on_click.plus;
	init_left_box_image(engine, &gui_box->children.data[0]);
	init_center_box_image(engine, &gui_box->children.data[1]);
	init_right_box_image(engine, &gui_box->children.data[2]);
}

static void	init_left_box_image(t_engine *engine, t_gui_box *gui_box)
{
	float	minus_line_thickness;

	if (init_image(&gui_box->image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		ft_fatal_error("Error during float input box creation");
	if (init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		ft_fatal_error("Error during float input box creation");
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	image_draw_outline(&gui_box->image, 2, COLOR_BLACK);
	minus_line_thickness = fminf(gui_box->image.width, gui_box->image.height);
	minus_line_thickness /= LINE_THICKNESS_DIVIDER;
	image_draw_minus(&gui_box->image, minus_line_thickness, BORDER,
		COLOR_WHITE);
	change_image_color(&gui_box->on_hover_image, HOVER_GUI_COLOR);
	image_draw_outline(&gui_box->on_hover_image, 2, COLOR_BLACK);
	minus_line_thickness = fminf(gui_box->on_hover_image.width,
			gui_box->on_hover_image.height);
	minus_line_thickness /= LINE_THICKNESS_DIVIDER;
	image_draw_minus(&gui_box->on_hover_image, minus_line_thickness, BORDER,
		COLOR_WHITE);
}

static void	init_center_box_image(t_engine *engine, t_gui_box *gui_box)
{
	if (init_image(&gui_box->image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		ft_fatal_error("Error during float input box creation");
	draw_center_box_image(&gui_box->image);
}

static void	init_right_box_image(t_engine *engine, t_gui_box *gui_box)
{
	float	plus_line_thickness;

	if (init_image(&gui_box->image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		ft_fatal_error("Error during float input box creation");
	if (init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		ft_fatal_error("Error during float input box creation");
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	image_draw_outline(&gui_box->image, 2, COLOR_BLACK);
	plus_line_thickness = fminf(gui_box->image.width, gui_box->image.height);
	plus_line_thickness /= LINE_THICKNESS_DIVIDER;
	image_draw_plus(&gui_box->image, plus_line_thickness, BORDER, COLOR_WHITE);
	change_image_color(&gui_box->on_hover_image, HOVER_GUI_COLOR);
	image_draw_outline(&gui_box->on_hover_image, 2, COLOR_BLACK);
	plus_line_thickness = fminf(gui_box->on_hover_image.width,
		gui_box->on_hover_image.height);
	plus_line_thickness /= LINE_THICKNESS_DIVIDER;
	image_draw_plus(&gui_box->on_hover_image, plus_line_thickness, BORDER,
		COLOR_WHITE);
}
