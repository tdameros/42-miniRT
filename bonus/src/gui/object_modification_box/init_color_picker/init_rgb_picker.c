/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rgb_picker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:24:11 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:24:11 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "engine.h"
#include "gui/box.h"
#include "gui/object_modification_box.h"

static void	init_rgb_picker_children(t_engine *minirt, t_gui_boxes *gui_boxes,
				t_gui_box *parent);

void	init_rgb_picker(t_engine *minirt, t_gui_box *gui_box)
{
	init_rgb_picker_children(minirt, &gui_box->children, gui_box);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
}

static void	init_rgb_picker_children(t_engine *minirt, t_gui_boxes *gui_boxes,
				t_gui_box *parent)
{
	gui_boxes->size = 2;
	gui_boxes->data = ft_calloc(gui_boxes->size, sizeof(*gui_boxes->data));
	if (gui_boxes->data == NULL)
		ft_fatal_error("init_rgb_picker_children: malloc failed");
	init_base_color_box(minirt, gui_boxes->data, parent);
	init_color_picker_box(minirt, gui_boxes->data + 1, parent);
	change_image_color(&gui_boxes->data[0].on_hover_image, COLOR_TRANSPARENT);
	change_image_color(&gui_boxes->data[1].on_hover_image, COLOR_TRANSPARENT);
}
