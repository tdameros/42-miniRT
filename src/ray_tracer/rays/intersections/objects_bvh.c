/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_bvh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 23:44:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/15 23:44:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "float.h"

#include "ray_tracer/rays.h"
#include "ray_tracer/bvh.h"

static void		objects_bvh_intersect(const t_ray *ray,
					const t_objects_bvh_node *node, t_hit *near_hit);
static t_hit	objects_bvh_intersect_leaf(const t_ray *ray,
					const t_objects_bvh_node *node, t_hit near_hit);

t_hit	objects_bvh_calculate_ray_intersection(const t_ray *ray,
											const t_objects_bvh_node *tree)
{
	t_hit	near_hit;

	near_hit = miss_hit();
	near_hit.distance = FLT_MAX;
	near_hit.index_obj = -1;
	objects_bvh_intersect(ray, tree, &near_hit);
	if (near_hit.index_obj >= 0 && near_hit.distance > 0)
		near_hit.hit = true;
	else
	{
		near_hit.hit = false;
		near_hit.distance = -1;
	}
	return (near_hit);
}

static void	objects_bvh_intersect(const t_ray *ray,
								const t_objects_bvh_node *node,
								t_hit *near_hit)
{
	if (node->is_leaf)
	{
		if (node->objects->length > 2
			&& !ray_intersect_aabb(ray, \
			node->aabb_min, node->aabb_max, near_hit->distance))
			return ;
		*near_hit = objects_bvh_intersect_leaf(ray, node, *near_hit);
	}
	else if (!ray_intersect_aabb(ray, node->aabb_min,
			node->aabb_max, near_hit->distance))
		return ;
	else
	{
		objects_bvh_intersect(ray, node->left_node, near_hit);
		objects_bvh_intersect(ray, node->right_node, near_hit);
	}
}

static t_hit	objects_bvh_intersect_leaf(const t_ray *ray,
										const t_objects_bvh_node *node,
										t_hit near_hit)
{
	size_t			i;
	t_hit			hit;
	const t_object	*object;

	i = 0;
	while (i < node->index_objects.length)
	{
		object = &node->objects->data[node->index_objects.data[i]];
		hit = calculate_object_distance(ray, object);
		hit.index_obj = node->index_objects.data[i];
		if (hit.distance > 0 && hit.distance < near_hit.distance)
			near_hit = hit;
		i++;
	}
	return (near_hit);
}
