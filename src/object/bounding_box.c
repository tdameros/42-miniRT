/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:13:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/17 09:13:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	object_calculate_aabb_min_max(t_object *object)
{
	t_vector3f	min;
	t_vector3f	max;

	min = object->bounding_box.top_face[0];
	min = vector3f_min(min, object->bounding_box.top_face[1]);
	min = vector3f_min(min, object->bounding_box.top_face[2]);
	min = vector3f_min(min, object->bounding_box.top_face[3]);
	min = vector3f_min(min, object->bounding_box.bottom_face[0]);
	min = vector3f_min(min, object->bounding_box.bottom_face[1]);
	min = vector3f_min(min, object->bounding_box.bottom_face[2]);
	min = vector3f_min(min, object->bounding_box.bottom_face[3]);
	max = object->bounding_box.top_face[0];
	max = vector3f_max(max, object->bounding_box.top_face[1]);
	max = vector3f_max(max, object->bounding_box.top_face[2]);
	max = vector3f_max(max, object->bounding_box.top_face[3]);
	max = vector3f_max(max, object->bounding_box.bottom_face[0]);
	max = vector3f_max(max, object->bounding_box.bottom_face[1]);
	max = vector3f_max(max, object->bounding_box.bottom_face[2]);
	max = vector3f_max(max, object->bounding_box.bottom_face[3]);
	object->bounding_box.aabb_min = min;
	object->bounding_box.aabb_max = max;
}

void	object_calculate_bounding_box(t_object *object)
{
	if (object->type == SPHERE)
		sphere_calculate_bounding_box(object);
	else if (object->type == CYLINDER)
		cylinder_calculate_bounding_box(object);
	else if (object->type == CONE)
		cone_calculate_bounding_box(object);
	else if (object->type == MESH)
		mesh_calculate_bounding_box(object);
}
