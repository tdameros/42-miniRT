/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:22:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/15 22:22:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/bvh.h"
#include "object.h"

t_aabb_split	split_bounding_box_mesh_node(t_mesh_bvh_node *node)
{
	const t_vector3f	extent = vector3f_subtract(node->aabb_max,
			node->aabb_min);
	t_aabb_split		result;

	result.axis = X_AXIS;
	if (extent.y > extent.x)
		result.axis = Y_AXIS;
	if (extent.z > vector3f_get(extent, result.axis))
		result.axis = Z_AXIS;
	result.middle = vector3f_get(node->aabb_min, result.axis)
		+ vector3f_get(extent, result.axis) * 0.5f;
	return (result);
}

t_side	get_face_side(t_mesh_bvh_node *node, int face_index, t_aabb_split split)
{
	bool		side[2];
	t_vector3f	vertex_a;
	t_vector3f	vertex_b;
	t_vector3f	vertex_c;

	side[0] = false;
	side[1] = false;
	vertex_a = mesh_get_vertex_from_face(node->mesh_object,
			face_index, 0);
	vertex_b = mesh_get_vertex_from_face(node->mesh_object,
			face_index, 1);
	vertex_c = mesh_get_vertex_from_face(node->mesh_object,
			face_index, 2);
	side[vector3f_get(vertex_a, split.axis) < split.middle] = true;
	side[vector3f_get(vertex_b, split.axis) < split.middle] = true;
	side[vector3f_get(vertex_c, split.axis) < split.middle] = true;
	if (side[0] && side[1])
		return (LEFT_AND_RIGHT);
	else if (side[0])
		return (LEFT);
	return (RIGHT);
}
