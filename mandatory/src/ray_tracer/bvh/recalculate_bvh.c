/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalculate_bvh.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:18:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/26 15:42:58 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/bvh.h"

static int	recalculate_object_bvh(t_object *object);

int	recalculate_bvh_scene(t_scene *scene, t_object *update_object)
{
	if (recalculate_object_bvh(update_object) < 0)
		return (-1);
	objects_bvh_free_tree(scene->bvh_tree);
	scene->bvh_tree = objects_bvh_create_tree(&scene->objects);
	if (scene->bvh_tree == NULL)
		return (-1);
	return (0);
}

static int	recalculate_object_bvh(t_object *object)
{
	if (object != NULL)
		object_calculate_bounding_box(object);
	return (0);
}
