/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light_attributes_modification_box.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:33:00 by vfries            #+#    #+#             */
/*   Updated: 2023/08/02 19:32:00 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"
#include "hooks.h"

void	init_light_attributes_modification_box(t_engine *engine,
			t_gui_box *gui_box)
{
	int	y;
	int	i;

	gui_box->children.size = 3;
	gui_box->children.data = ft_calloc(gui_box->children.size,
			sizeof(*gui_box->children.data));
	if (gui_box->children.data == NULL)
		ft_fatal_error("init_light_attributes_modification_box: "
			"malloc failed");
	i = 0;
	add_delete_box(engine, gui_box->children.data + i++, gui_box);
	y = get_transformations_boxes_index(gui_box);
	add_position_box(engine, gui_box->children.data + i++, &y, gui_box);
	add_brightness_box(engine, gui_box->children.data + i, &y, gui_box);
}
