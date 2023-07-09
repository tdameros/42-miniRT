/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:13:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/03 00:13:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"

void	normal_input_box_x_on_click_plus(t_gui_box *self, t_engine *engine,
										int y, int x)
{
	t_object			*object;

	(void)self;
	(void)y;
	(void)x;
	object = engine->gui.selected_object;
	if (object == NULL)
		return ;
	object_rotate(object, (t_vector3f){1.f, 0.f, 0.f},
		engine->gui.object_rotation_degrees);
	engine->scene_changed = true;
}

void	normal_input_box_x_on_click_minus(t_gui_box *self, t_engine *engine,
										int y, int x)
{
	t_object			*object;

	(void)self;
	(void)y;
	(void)x;
	object = engine->gui.selected_object;
	if (object == NULL)
		return ;
	object_rotate(object, (t_vector3f){1.f, 0.f, 0.f},
		-engine->gui.object_rotation_degrees);
	engine->scene_changed = true;
}
