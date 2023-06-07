/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation_on_clicks.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:59:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/07 09:59:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"

#define DEFAULT_DISTANCE 10.f

void	sphere_create_on_click(t_gui_box *self, t_engine *engine, int y, int x)
{
	const t_color		color = {
		.x = engine->gui.color_picker_base_color.x / 255.f,
		.y = engine->gui.color_picker_base_color.y / 255.f,
		.z = engine->gui.color_picker_base_color.z / 255.f
	};
	const t_object		object = sphere_create(vector3f_create(0, 0, 0), 0.5f,
			color);

	if (add_object_in_objects(&engine->scene.objects, object) < 0)
	{
		ft_print_error("Failed to create new sphere\n");
		return ;
	}
	engine->object_being_placed_distance = 10;
	engine->object_being_placed = engine->scene.objects.data
		+ engine->scene.objects.length - 1;
	(void)self;
	(void)y;
	(void)x;
}
