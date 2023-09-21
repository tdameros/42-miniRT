/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalculate_bvh.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:18:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/20 18:18:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/bvh.h"

int	recalculate_bvh_scene(t_scene *scene, t_object *update_object)
{
	size_t	i;

	if (update_object != NULL)
	{
		object_calculate_bounding_box(update_object);
		if (update_object->type == MESH)
		{
			// TODO: secure it
			mesh_bvh_free_tree(update_object->mesh.tree);
			update_object->mesh.tree = mesh_bvh_create_tree(update_object);
		}
	}
	i = 0;
	while (i < scene->objects.length)
	{
		if (scene->objects.data[i].type == MESH)
			mesh_bvh_update_tree(&scene->objects.data[i],
				scene->objects.data[i].mesh.tree);
		i++;
	}
	objects_bvh_free_tree(scene->bvh_tree);
	scene->bvh_tree = objects_bvh_create_tree(&scene->objects);
	return (0);
}
