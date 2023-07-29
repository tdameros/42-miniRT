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

#include "gui/box.h"
#include "gui/utils.h"

static int	error_during_float_input_box_creation(t_engine *engine,
				t_gui_box *gui_box);

int	create_float_input_box(t_engine *engine, t_gui_box *gui_box,
		t_float_input_box_on_click on_click)
{
	if (create_horizontal_boxes(engine, gui_box, "20 60 20", 0) < 0)
		return (-1);
	gui_box->children.data[0].on_click = on_click.minus;
	gui_box->children.data[1].on_click = on_click.text_box;
	gui_box->children.data[2].on_click = on_click.plus;
	if (init_left_box_image(engine, &gui_box->children.data[0]) < 0)
		return (error_during_float_input_box_creation(engine, gui_box));
	if (init_center_box_image(engine, &gui_box->children.data[1]) < 0)
		return (error_during_float_input_box_creation(engine, gui_box));
	if (init_right_box_image(engine, &gui_box->children.data[2]) < 0)
		return (error_during_float_input_box_creation(engine, gui_box));
	return (0);
}

static int	error_during_float_input_box_creation(t_engine *engine,
				t_gui_box *gui_box)
{
	destroy_t_image(&engine->window, &gui_box->children.data[0].image);
	destroy_t_image(&engine->window, &gui_box->children.data[0].on_hover_image);
	destroy_t_image(&engine->window, &gui_box->children.data[1].image);
	destroy_t_image(&engine->window, &gui_box->children.data[1].on_hover_image);
	destroy_t_image(&engine->window, &gui_box->children.data[2].image);
	destroy_t_image(&engine->window, &gui_box->children.data[2].on_hover_image);
	free(gui_box->children.data);
	ft_bzero(&gui_box->children, sizeof(gui_box->children));
	return (-1);
}
