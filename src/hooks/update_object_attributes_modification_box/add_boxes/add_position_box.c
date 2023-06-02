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
#include <stdlib.h>

#include "gui/box.h"
#include "gui/utils.h"

static int	init_position_box_children(t_engine *engine, t_gui_box *gui_box);
static int	add_position_text_box(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent);
static int	add_position_buttons(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent);
static int	init_position_buttons_children(t_engine *engine,
				t_gui_box *gui_box);

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
	gui_box->children.size = 2;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
			* gui_box->children.size);
	if (gui_box->children.data == NULL)
	{
		gui_box->children.size = 0;
		return (-1);
	}
	if (add_position_text_box(engine, gui_box->children.data, gui_box) < 0)
	{
		free(gui_box->children.data);
		gui_box->children.data = NULL;
		gui_box->children.size = 0;
		return (-1);
	}
	if (add_position_buttons(engine, gui_box->children.data + 1, gui_box)
		>= 0)
		return (0);
	// TODO destroy position_text_box
	free(gui_box->children.data);
	gui_box->children.data = NULL;
	gui_box->children.size = 0;
	return (-1);
}

static int	add_position_text_box(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, parent, \
		(t_vector2i){
			.x = 4,
			.y = 2}, \
		(t_vector2i){
			.x = parent->size.x - 8,
			.y = parent->size.y / 3 - 2});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	gui_box->draw = &default_gui_box_draw;
	return (0);
}

static int	add_position_buttons(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, parent, \
		(t_vector2i){
			.x = 0,
			.y = parent->size.y / 3 + 4}, \
		(t_vector2i){
			.x = parent->size.x,
			.y = parent->size.y / 3 * 2 - 8});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
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
	if (create_n_horizontal_boxes(engine, gui_box, 3, 4) < 0)
		return (ft_print_error("create n horizontal box failed"), -1);
	if (create_float_input_box(engine, gui_box->children.data,
			&default_gui_box_on_click) < 0)
	{
		destroy_t_image(&engine->window, &gui_box->children.data[0].image);
		destroy_t_image(&engine->window, &gui_box->children.data[1].image);
		destroy_t_image(&engine->window, &gui_box->children.data[2].image);
		ft_bzero(gui_box->children.data + 0, sizeof(*gui_box->children.data));
		ft_bzero(gui_box->children.data + 1, sizeof(*gui_box->children.data));
		ft_bzero(gui_box->children.data + 2, sizeof(*gui_box->children.data));
		return (-1);
	}
	gui_box->children.data[0].draw = &default_gui_box_draw;
	gui_box->children.data[1].draw = &default_gui_box_draw;
	gui_box->children.data[2].draw = &default_gui_box_draw;
	return (0);
}
