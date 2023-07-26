/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_toggle_box.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 22:34:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/20 22:34:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <math.h>

#include "engine.h"
#include "gui/box.h"
#include "gui/object_modification_box.h"
#include "hooks.h"
#include "gui/UI.h"
#include "colors.h"

#define OFFSET 4

static int	init_toggle_box_children(t_engine *engine, t_gui_box *gui_box);
static int	init_toggle_box_button(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent, int button_size);
static int	init_toggle_box_text_box(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent, int button_size);

int	add_toggle_box(t_engine *engine, t_gui_box *gui_box, int *i,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent, \
		(t_vector2i){
			.x = 0,
			.y = *i}, \
		(t_vector2i){
			.x = parent->size.x,
			.y = get_normal_box_size(parent)}, \
		true});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	*i += gui_box->size.y + OBJECT_ATTRIBUTE_BOX_OFFSET;
	if (init_toggle_box_children(engine, gui_box) < 0)
	{
		destroy_t_image(&engine->window, &gui_box->image);
		ft_bzero(gui_box, sizeof(*gui_box));
		return (-1);
	}
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	return (0);
}

static int	init_toggle_box_children(t_engine *engine, t_gui_box *gui_box)
{
	int	button_size;

	gui_box->children.size = 2;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
			* gui_box->children.size);
	if (gui_box->children.data == NULL)
		return (ft_bzero(&gui_box->children, sizeof(gui_box->children)), -1);
	button_size = fminf(gui_box->size.x - OFFSET * 2, \
						gui_box->size.y - OFFSET * 2);
	if (init_toggle_box_button(engine, gui_box->children.data, gui_box,
			button_size) < 0)
	{
		free(gui_box->children.data);
		return (ft_bzero(&gui_box->children, sizeof(gui_box->children)), -1);
	}
	if (init_toggle_box_text_box(engine, gui_box->children.data + 1, gui_box,
			button_size) < 0)
	{
		free(gui_box->children.data);
		//TODO free
		return (ft_bzero(&gui_box->children, sizeof(gui_box->children)), -1);
	}
	return (0);
}

static int	init_toggle_box_button(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent, const int button_size)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent, \
		(t_vector2i){
			.x = OFFSET,
			.y = OFFSET}, \
		(t_vector2i){
			.x = button_size,
			.y = button_size}, \
		true});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	if (init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
			gui_box->size.y) < 0)
		return (-1); // TODO free
	return (0);
}

static int	init_toggle_box_text_box(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent, const int button_size)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent, \
		(t_vector2i){
			.x = button_size + OFFSET * 2,
			.y = 0}, \
		(t_vector2i){
			.x = parent->size.x - (button_size + OFFSET * 3),
			.y = parent->size.y}, \
		true});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	return (0);
}
