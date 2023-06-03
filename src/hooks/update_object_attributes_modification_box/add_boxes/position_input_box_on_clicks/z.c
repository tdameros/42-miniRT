/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:15:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/03 00:15:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"

void	position_input_box_z_on_click_plus(struct s_gui_box *self,
			t_engine *engine, int y, int x)
{
	t_object	*object;

	(void)self;
	(void)y;
	(void)x;
	object = engine->gui.selected_object;
	if (object == NULL)
		return ;
	object->position.z
		+= engine->gui.object_modification_amount;
	if (object->type == PLANE)
		object->d = -vector3f_dot(object->normal, object->position);
}

void	position_input_box_z_on_click_minus(struct s_gui_box *self,
			t_engine *engine, int y, int x)
{
	t_object	*object;

	(void)self;
	(void)y;
	(void)x;
	object = engine->gui.selected_object;
	if (object == NULL)
		return ;
	object->position.z
		-= engine->gui.object_modification_amount;
	if (object->type == PLANE)
		object->d = -vector3f_dot(object->normal, object->position);
}
