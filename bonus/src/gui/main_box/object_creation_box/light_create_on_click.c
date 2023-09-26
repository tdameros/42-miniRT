/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_create_on_click.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 23:11:25 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 23:13:40 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "events.h"
#include "hooks.h"
#include "ray_tracer_gui_api.h"

void	light_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	const t_vector3f	light_color = engine->gui.color_and_material.\
			material_to_assign_to_new_objects.albedo;
	t_light				light;

	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	light = light_create(vector3f_create(0, 0, 0), light_color, 0.5f);
	add_light(engine, light);
	engine->object_being_placed_distance = DEFAULT_DISTANCE_OF_NEW_OBJECTS;
	engine->object_being_placed.light
		= &engine->scene.lights.data[engine->scene.lights.length - 1];
	update_object_attributes_modification_box(engine);
	(void)self;
}
