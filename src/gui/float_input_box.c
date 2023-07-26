/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_float_input_box.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:55:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/02 17:55:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

#include "gui/box.h"
#include "gui/utils.h"
#include "gui/UI.h"
#include "font/render.h"
#include "gui/main_gui_box.h"

#define BORDER 4
#define LINE_THICKNESS_DIVIDER 11
#define SPRINTF_PARAM "%.2f"

static int	init_left_box_image(t_engine *engine, t_gui_box *gui_box);
static int	init_center_box_image(t_engine *engine, t_gui_box *gui_box);
static void	draw_center_box_image(t_image *image);
static int	init_right_box_image(t_engine *engine, t_gui_box *gui_box);

void	update_float_input_box(const t_engine *engine, const float f,
			t_gui_box *input_box)
{
	size_t	size;
	char	*buffer;

	if (input_box == NULL)
		return ;
	draw_center_box_image(&input_box->children.data[1].image);
	size = snprintf(NULL, 0, SPRINTF_PARAM, f) + 1;
	buffer = malloc(size);
	if (buffer == NULL)
		return (write_centered_string_to_image(&engine->gui.font,
				&input_box->children.data[1].image, "ENOMEM"));
	snprintf(buffer, size, SPRINTF_PARAM, f);
	write_centered_string_to_image(&engine->gui.font,
		&input_box->children.data[1].image, buffer);
	free(buffer);
}

int	create_float_input_box(t_engine *engine, t_gui_box *gui_box,
		t_float_input_box_on_click on_click)
{
	if (create_horizontal_boxes(engine, gui_box, "20 60 20", 0) < 0)
		return (-1);
	gui_box->children.data[0].on_click = on_click.minus;
	gui_box->children.data[1].on_click = on_click.text_box;
	gui_box->children.data[2].on_click = on_click.plus;
	if (init_left_box_image(engine, &gui_box->children.data[0]) < 0)
		return (-1); // TODO free stuff
	if (init_center_box_image(engine, &gui_box->children.data[1]) < 0)
		return (-1); // TODO free stuff
	if (init_right_box_image(engine, &gui_box->children.data[2]) < 0)
		return (-1); // TODO free stuff
	return (0);
}

static int	init_left_box_image(t_engine *engine, t_gui_box *gui_box)
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

static int	init_center_box_image(t_engine *engine, t_gui_box *gui_box)
{
	if (init_image(&gui_box->image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		return (-1);
	draw_center_box_image(&gui_box->image);
	return (0);
}

static void	draw_center_box_image(t_image *image)
{
	change_image_color(image, SUB_GUI_COLOR);
	image_draw_top_outline(image, 2, COLOR_BLACK);
	image_draw_bottom_outline(image, 2, COLOR_BLACK);
}

static int	init_right_box_image(t_engine *engine, t_gui_box *gui_box)
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
