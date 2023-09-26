/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_ppm_box.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:37:19 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 18:37:19 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "ray_tracer_gui_api.h"

void	click_mesh_box(t_engine *engine, size_t index)
{
	t_material	material;
	t_object	object;

	if (engine->object_being_placed.object || engine->object_being_placed.light)
		return ;
	ft_bzero(&material, sizeof(material));
	if (material_deep_copy(&material,
			&engine->gui.color_and_material.material_to_assign_to_new_objects)
		< 0)
		return ((void)ft_print_error("Warning: Failed to create new mesh " \
									"object, material allocation failed\n"));
	mesh_object_initialize(&object, engine->gui.mesh_objects.mesh_files[index],
		material);
	add_object(engine, object);
	engine->object_being_placed_distance = DEFAULT_DISTANCE_OF_NEW_OBJECTS;
	engine->object_being_placed.object
		= &engine->scene.objects.data[engine->scene.objects.length - 1];
	update_object_attributes_modification_box(engine);
}
