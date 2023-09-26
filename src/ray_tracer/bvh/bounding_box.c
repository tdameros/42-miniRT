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

t_aabb_split	split_bounding_box_objects_node(t_objects_bvh_node *node)
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

t_side	get_bounding_box_side(t_bounding_box *bh, t_aabb_split split)
{
	bool	side[2];
	size_t	i;

	side[0] = false;
	side[1] = false;
	i = 0;
	while (i < 4)
	{
		side[vector3f_get(bh->top_face[i], split.axis) \
		< split.middle] = true;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		side[vector3f_get(bh->bottom_face[i], split.axis) \
		< split.middle] = true;
		i++;
	}
	if (side[0] && side[1])
		return (LEFT_AND_RIGHT);
	else if (side[0])
		return (LEFT);
	return (RIGHT);
}
