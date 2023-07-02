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
#include "math/quaternion.h"

void	normal_input_box_y_on_click_plus(struct s_gui_box *self,
			t_engine *engine, int y, int x)
{
	t_object			*object;
	const float			degrees = engine->gui.object_rotation_degrees;
	const t_vector3f	rotation_axis = vector3f_create(0, 1, 0);

	(void)self;
	(void)y;
	(void)x;
	object = engine->gui.selected_object;
	if (object == NULL)
		return ;
	object->normal = vector3f_unit(\
	quaternionf_rotate_vector3f(degrees, rotation_axis, object->normal));
}

void	normal_input_box_y_on_click_minus(struct s_gui_box *self,
			t_engine *engine, int y, int x)
{
	t_object			*object;
	const float			degrees = -engine->gui.object_rotation_degrees;
	const t_vector3f	rotation_axis = vector3f_create(0, 1, 0);

	(void)self;
	(void)y;
	(void)x;
	object = engine->gui.selected_object;
	if (object == NULL)
		return ;
	object->normal = vector3f_unit(\
	quaternionf_rotate_vector3f(degrees, rotation_axis, object->normal));
}
