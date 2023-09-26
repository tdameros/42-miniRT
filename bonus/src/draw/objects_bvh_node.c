/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_bvh_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:27:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/17 15:27:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	draw_objects_bvh_objects_node(t_engine *engine,
				const t_objects_bvh_node *node, t_vector3f color);

void	draw_objects_bvh_node(t_engine *engine, const t_objects_bvh_node *node,
							t_vector3f color)
{
	const t_vector3f	max = node->aabb_max;
	const t_vector3f	min = node->aabb_min;
	t_bounding_box		bounding_box;

	bounding_box.top_face[0] = (t_vector3f){max.x, max.y, min.z};
	bounding_box.top_face[1] = max;
	bounding_box.top_face[2] = (t_vector3f){min.x, max.y, max.z};
	bounding_box.top_face[3] = (t_vector3f){min.x, max.y, min.z};
	bounding_box.bottom_face[0] = (t_vector3f){max.x, min.y, min.z};
	bounding_box.bottom_face[1] = (t_vector3f){max.x, min.y, max.z};
	bounding_box.bottom_face[2] = (t_vector3f){min.x, min.y, max.z};
	bounding_box.bottom_face[3] = min;
	draw_bounding_box(engine, &bounding_box, color);
	if (node->is_leaf)
		draw_objects_bvh_objects_node(engine, node,
			(t_vector3f){255.f, 255.f, 255.f});
}

static void	draw_objects_bvh_objects_node(t_engine *engine,
										const t_objects_bvh_node *node,
										t_vector3f color)
{
	size_t		i;
	t_object	*object;

	i = 0;
	while (i < node->index_objects.length)
	{
		object = &node->objects->data[node->index_objects.data[i]];
		if (object->type != PLANE)
			draw_bounding_box(engine, &object->bounding_box, color);
		i++;
	}
}
