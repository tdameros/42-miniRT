/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:15:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/03 00:15:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "gui/box.h"

void	normal_input_box_y_on_click_plus(struct s_gui_box *self,
			t_engine *engine, int y, int x)
{
	t_object			*object;
	const float			change = engine->gui.object_modification_amount;

	(void)self;
	(void)y;
	(void)x;
	object = engine->gui.selected_object;
	if (object == NULL)
		return ;
	object->normal \
		= vector3f_normalize((t_vector3f){\
			.x = object->normal.x, \
			.y = object->normal.y + change, \
			.z = object->normal.z
	});
	if (object->type == PLANE)
		object->d = -vector3f_dot(object->normal, object->position);
}

void	normal_input_box_y_on_click_minus(struct s_gui_box *self,
			t_engine *engine, int y, int x)
{
	t_object			*object;
	const float			change = engine->gui.object_modification_amount;

	(void)self;
	(void)y;
	(void)x;
	object = engine->gui.selected_object;
	if (object == NULL)
		return ;
	object->normal \
		= vector3f_normalize((t_vector3f){\
			.x = object->normal.x, \
			.y = object->normal.y - change, \
			.z = object->normal.z
	});
	if (object->type == PLANE)
		object->d = -vector3f_dot(object->normal, object->position);
}
