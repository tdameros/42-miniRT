/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_position_box.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:24:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/01 13:24:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "gui/box.h"
#include "gui/utils.h"
#include "hooks.h"

static int	init_position_box_children(t_engine *engine, t_gui_box *gui_box);
static int	add_position_buttons(t_engine *engine, t_gui_box *gui_box);
static int	init_position_buttons_children(t_engine *engine,
				t_gui_box *gui_box);
static int	create_position_input_box(t_engine *engine, t_gui_box *gui_box,
				const char *type);

int	add_position_box(t_engine *engine, t_gui_box *gui_box, int *i,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, parent, \
		(t_vector2i){
			.x = 0,
			.y = *i}, \
		(t_vector2i){
			.x = parent->size.x,
			.y = 75});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	*i += gui_box->size.y + 8;
	if (init_position_box_children(engine, gui_box) < 0)
	{
		destroy_t_image(&engine->window, &gui_box->image);
		ft_bzero(gui_box, sizeof(*gui_box));
		return (-1);
	}
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	change_image_color(&gui_box->image, 0x40202020);
	round_image_corners(&gui_box->image, 10);
	return (0);
}

static int	init_position_box_children(t_engine *engine, t_gui_box *gui_box)
{
	// TODO leaks
	if (create_vertical_boxes(engine, gui_box, "40 60") < 0)
		return (-1);
	if (add_position_buttons(engine, gui_box->children.data + 1) < 0)
		return (-1);
	change_image_color(&gui_box->children.data[0].image, COLOR_TRANSPARENT);
//	write_centered_string_to_image(engine, &gui_box->children.data[0].image,
//		"Position");
	return (0);
}

static int	add_position_buttons(t_engine *engine, t_gui_box *gui_box)
{
	if (init_position_buttons_children(engine, gui_box) < 0)
	{
		destroy_t_image(&engine->window, &gui_box->image);
		ft_bzero(gui_box, sizeof(*gui_box));
		return (-1);
	}
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	round_image_corners(&gui_box->image, 10);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	return (0);
}

static int	init_position_buttons_children(t_engine *engine, t_gui_box *gui_box)
{
	// TODO leaks
	if (create_n_horizontal_boxes(engine, gui_box, 3, 4) < 0)
		return (ft_print_error("create n horizontal box failed"), -1);
	if (create_position_input_box(engine, gui_box->children.data + 0, "x") < 0)
		return (-1);
	if (create_position_input_box(engine, gui_box->children.data + 1, "y") < 0)
		return (-1);
	if (create_position_input_box(engine, gui_box->children.data + 2, "z") < 0)
		return (-1);
	gui_box->draw = &default_gui_box_draw;
	return (0);
}

static int	create_position_input_box(t_engine *engine, t_gui_box *gui_box,
				const char *type)
{
	// TODO leaks
	t_float_input_box_on_click	on_click = {0};

	(void)type;
	if (type[0] == 'x')
	{
		on_click.plus = &position_input_box_x_on_click_plus;
		on_click.minus = &position_input_box_x_on_click_minus;
	}
	if (type[0] == 'y')
	{
		on_click.plus = &position_input_box_y_on_click_plus;
		on_click.minus = &position_input_box_y_on_click_minus;
	}
	if (type[0] == 'z')
	{
		on_click.plus = &position_input_box_z_on_click_plus;
		on_click.minus = &position_input_box_z_on_click_minus;
	}
	if (create_vertical_boxes(engine, gui_box, "40 55 5") < 0)
		return (-1);
	if (create_float_input_box(engine,
			gui_box->children.data + 1, on_click) < 0)
		return (-1);
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	change_image_color(&gui_box->children.data[0].image, COLOR_SAND);
	change_image_color(&gui_box->children.data[2].image, COLOR_TRANSPARENT);
//	write_centered_string_to_image(engine, &gui_box->children.data[0].image,
//		type);
	gui_box->draw = &default_gui_box_draw;
//	gui_box->children.data[0].draw = &default_gui_box_draw;
	gui_box->children.data[1].draw = &default_gui_box_draw;
	return (0);
}
