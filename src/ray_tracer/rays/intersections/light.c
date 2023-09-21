/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/18 18:47:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "float.h"

#include "ray_tracer/rays.h"

static t_hit	objects_bvh_calculate_light_intersection(const t_ray *ray,
					const t_objects_bvh_node *tree, const float light_distance);
static int		objects_bvh_light_intersect(const t_ray *ray,
					const t_objects_bvh_node *node,
					t_hit *near_hit, const float light_distance);
static t_hit	objects_bvh_light_intersect_leaf(const t_ray *ray,
					const t_objects_bvh_node *node,
					t_hit near_hit, const float light_distance);

t_hit	calculate_shadow_ray_intersection(const t_ray *ray,
										const float light_distance,
										const t_scene *scene)
{
	size_t		index;
	t_hit		hit;
	t_hit		bvh_hit;

	index = 0;
	while (index < scene->plane_indexes.length)
	{
		hit = calculate_plane_distance(ray, scene->objects.data
				+ scene->plane_indexes.data[index]);
		if (hit.distance > 0.f && hit.distance < light_distance)
			return (hit_object(ray, scene->objects.data + index, hit));
		index++;
	}
	bvh_hit = objects_bvh_calculate_light_intersection(ray,
			scene->bvh_tree, light_distance);
	if (bvh_hit.hit)
		return (bvh_hit);
	return (miss_hit());
}

static t_hit	objects_bvh_calculate_light_intersection(const t_ray *ray,
												const t_objects_bvh_node *tree,
												const float light_distance)
{
	t_hit	near_hit;

	near_hit = miss_hit();
	near_hit.distance = FLT_MAX;
	near_hit.index_obj = -1;
	objects_bvh_light_intersect(ray, tree, &near_hit, light_distance);
	if (near_hit.index_obj >= 0 && near_hit.distance > 0)
		near_hit.hit = true;
	else
	{
		near_hit.hit = false;
		near_hit.distance = -1;
	}
	return (near_hit);
}

static int	objects_bvh_light_intersect(const t_ray *ray,
										const t_objects_bvh_node *node,
										t_hit *near_hit,
										const float light_distance)
{
	if (node->is_leaf)
	{
		if (node->objects->length > 2
			&& !ray_intersect_aabb(ray, \
			node->aabb_min, node->aabb_max, near_hit->distance))
			return (0);
		*near_hit = objects_bvh_light_intersect_leaf(ray, node, *near_hit,
				light_distance);
		if (near_hit->hit)
			return (1);
	}
	else if (!ray_intersect_aabb(ray, node->aabb_min,
			node->aabb_max, near_hit->distance))
		return (0);
	else
	{
		if (objects_bvh_light_intersect(ray,
				node->left_node, near_hit, light_distance))
			return (1);
		if (objects_bvh_light_intersect(ray, node->right_node,
				near_hit, light_distance))
			return (1);
	}
	return (0);
}

static t_hit	objects_bvh_light_intersect_leaf(const t_ray *ray,
												const t_objects_bvh_node *node,
												t_hit near_hit,
												const float light_distance)
{
	size_t			i;
	t_hit			hit;
	const t_object	*object;

	i = 0;
	while (i < node->index_objects.length)
	{
		object = &node->objects->data[node->index_objects.data[i]];
		hit = calculate_object_distance(ray, object);
		if (hit.distance > 0 && hit.distance < light_distance)
		{
			near_hit = hit;
			near_hit.index_obj = node->index_objects.data[i];
			near_hit.hit = true;
			return (near_hit);
		}
		i++;
	}
	return (near_hit);
}
