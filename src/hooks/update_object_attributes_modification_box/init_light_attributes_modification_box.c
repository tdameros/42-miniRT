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

#include <stdlib.h>

#include "gui/box.h"
#include "hooks.h"

void	init_light_attributes_modification_box(t_engine *engine,
			t_gui_box *gui_box)
{
	int	i;

	gui_box->children.size = 2;
	gui_box->children.data = ft_calloc(gui_box->children.size,
			sizeof(*gui_box->children.data));
	if (gui_box->children.data == NULL)
		ft_fatal_error("init_light_attributes_modification_box: "
			"malloc failed");
	i = 0;
	add_position_box(engine, gui_box->children.data, &i, gui_box);
	add_brightness_box(engine, gui_box->children.data + 1, &i, gui_box);
}
