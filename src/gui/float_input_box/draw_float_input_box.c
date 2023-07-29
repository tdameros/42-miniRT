/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_float_input_box.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:30:59 by vincent           #+#    #+#             */
/*   Updated: 2023/07/29 19:31:17 by vincent          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "engine.h"
#include "gui/box.h"
#include "gui/UI.h"
#include "gui/utils.h"

#define LINE_THICKNESS_DIVIDER 11
#define BORDER 4

int	init_left_box_image(t_engine *engine, t_gui_box *gui_box)
{
	float	minus_line_thickness;

	if (init_image(&gui_box->image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		return (-1);
	if (init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		return (destroy_t_image(&engine->window, &gui_box->image), -1);
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
	return (0);
}

int	init_center_box_image(t_engine *engine, t_gui_box *gui_box)
{
	if (init_image(&gui_box->image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		return (-1);
	draw_center_box_image(&gui_box->image);
	return (0);
}

void	draw_center_box_image(t_image *image)
{
	change_image_color(image, SUB_GUI_COLOR);
	image_draw_top_outline(image, 2, COLOR_BLACK);
	image_draw_bottom_outline(image, 2, COLOR_BLACK);
}

int	init_right_box_image(t_engine *engine, t_gui_box *gui_box)
{
	float	plus_line_thickness;

	if (init_image(&gui_box->image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		return (-1);
	if (init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		return (destroy_t_image(&engine->window, &gui_box->image), -1);
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
	return (0);
}
