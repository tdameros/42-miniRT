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

static int	init_position_box_children(t_engine *engine, t_gui_box *gui_box);
static int	add_position_text_box(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent);

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
	if (errno == EINVAL)
		return (-1);
	// TODO check image creation
	*i += gui_box->size.y + 8;
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	change_image_color(&gui_box->image, 0x40202020);
	round_image_corners(&gui_box->image, 10);
	if (init_position_box_children(engine, gui_box) < 0)
		return (-1); // TODO free gui_box content
	return (0);
}

static int	init_position_box_children(t_engine *engine, t_gui_box *gui_box)
{
	gui_box->children.size = 2;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
			* gui_box->children.size);
	if (gui_box->children.data == NULL)
		return (-1);
	if (add_position_text_box(engine, gui_box->children.data, gui_box) < 0)
		return (free(gui_box->children.data), -1);
	return (0);
}

static int	add_position_text_box(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, parent, \
		(t_vector2i){
			.x = 0,
			.y = 0}, \
		(t_vector2i){
			.x = parent->size.x,
			.y = parent->size.y / 3});
	(void)engine;(void)parent;(void)gui_box;
	return (0);
}
