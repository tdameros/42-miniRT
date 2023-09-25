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

static int	recalculate_object_bvh(t_object *object);

int	recalculate_bvh_scene(t_scene *scene, t_object *update_object)
{
	size_t	i;

	if (recalculate_object_bvh(update_object) < 0)
		return (-1);
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
	if (scene->bvh_tree == NULL)
		return (-1);
	return (0);
}

static int	recalculate_object_bvh(t_object *object)
{
	if (object != NULL)
	{
		object_calculate_bounding_box(object);
		if (object->type == MESH)
		{
			mesh_bvh_free_tree(object->mesh.tree);
			object->mesh.tree = mesh_bvh_create_tree(object);
			if (object->mesh.tree == NULL)
				return (-1);
		}
	}
	return (0);
}
