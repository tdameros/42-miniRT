/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:16:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/03 00:16:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "gui/box.h"

void	position_input_box_z_on_click_plus(struct s_gui_box *self,
			t_engine *engine, int y, int x)
{
	(void)self;
	(void)y;
	(void)x;
	if (engine->gui.selected_object == NULL)
		return ;
	engine->gui.selected_object->position.z += 0.1f;
}

void	position_input_box_z_on_click_minus(struct s_gui_box *self,
			t_engine *engine, int y, int x)
{
	(void)self;
	(void)y;
	(void)x;
	if (engine->gui.selected_object == NULL)
		return ;
	engine->gui.selected_object->position.z -= 0.1f;
}
