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

static void		mesh_bvh_intersect(const t_ray *ray,
					const t_mesh_bvh_node *node, t_hit *near_hit);
static t_hit	mesh_bvh_intersect_leaf(const t_ray *ray,
					const t_mesh_bvh_node *node, t_hit near_hit);
static float	calculate_face_distance(const t_ray *ray, const t_object *mesh,
					const t_mesh_face *face);
static float	calculate_moller_triangle_distance(const t_ray *ray,
					const t_vector3f vertex[3], const t_vector3f edge[2]);

t_hit	mesh_bvh_calculate_ray_intersection(const t_ray *ray,
											const t_mesh_bvh_node *tree)
{
	t_hit	near_hit;

	near_hit = miss_hit();
	near_hit.distance = FLT_MAX;
	near_hit.index_obj = -1;
	mesh_bvh_intersect(ray, tree, &near_hit);
	if (near_hit.hit && near_hit.distance > 0)
		near_hit.hit = true;
	else
	{
		near_hit.hit = false;
		near_hit.distance = -1;
	}
	return (near_hit);
}

static void	mesh_bvh_intersect(const t_ray *ray,
								const t_mesh_bvh_node *node,
								t_hit *near_hit)
{
	if (node->is_leaf)
	{
		if (node->index_faces.length > 2
			&& !ray_intersect_aabb(ray, \
			node->aabb_min, node->aabb_max, near_hit->distance))
			return ;
		*near_hit = mesh_bvh_intersect_leaf(ray, node, *near_hit);
	}
	else if (!ray_intersect_aabb(ray, node->aabb_min,
			node->aabb_max, near_hit->distance))
		return ;
	else
	{
		mesh_bvh_intersect(ray, node->left_node, near_hit);
		mesh_bvh_intersect(ray, node->right_node, near_hit);
	}
}

static t_hit	mesh_bvh_intersect_leaf(const t_ray *ray,
										const t_mesh_bvh_node *node,
										t_hit near_hit)
{
	size_t				i;
	const t_mesh_face	*face;
	float				distance;

	i = 0;
	while (i < node->index_faces.length)
	{
		face = &node->mesh_object->mesh.faces.data[node->index_faces.data[i]];
		distance = calculate_face_distance(ray, node->mesh_object, face);
		if (distance > 0 && distance < near_hit.distance)
		{
			near_hit.distance = distance;
			near_hit.normal = node->mesh_object->cache.mesh.normals.data \
				[face->vertex_a.y - 1];
			near_hit.hit = true;
		}
		i++;
	}
	return (near_hit);
}

static float	calculate_face_distance(const t_ray *ray, const t_object *mesh,
										const t_mesh_face *face)
{
	const t_vector3f	vertex_a
		= mesh->cache.mesh.vertex.data[face->vertex_a.x - 1];
	const t_vector3f	vertex_b
		= mesh->cache.mesh.vertex.data[face->vertex_b.x - 1];
	const t_vector3f	vertex_c
		= mesh->cache.mesh.vertex.data[face->vertex_c.x - 1];
	const t_vector3f	edge_1 = vector3f_subtract(vertex_b, vertex_a);
	const t_vector3f	edge_2 = vector3f_subtract(vertex_c, vertex_a);

	return (calculate_moller_triangle_distance(ray, \
		(t_vector3f[3]){vertex_a, vertex_b, vertex_c}, \
		(t_vector3f[2]){edge_1, edge_2}));
}

/*
https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
*/
static float	calculate_moller_triangle_distance(const t_ray *ray,
												const t_vector3f vertex[3],
												const t_vector3f edge[2])
{
	const t_vector3f	h = vector3f_cross(ray->direction, edge[1]);
	const float			a = vector3f_dot(edge[0], h);
	float				f;
	t_vector3f			sq[2];
	float				uv[2];

	if (ft_is_equalsf(a, 0, FLT_EPSILON))
		return (-1);
	f = 1.f / a;
	sq[0] = vector3f_subtract(ray->origin, vertex[0]);
	uv[0] = f * vector3f_dot(sq[0], h);
	if (uv[0] < 0.f || uv[0] > 1.f)
		return (-1);
	sq[1] = vector3f_cross(sq[0], edge[0]);
	uv[1] = f * vector3f_dot(ray->direction, sq[1]);
	if (uv[1] < 0.f || uv[0] + uv[1] > 1.f)
		return (-1);
	return (f * vector3f_dot(edge[1], sq[1]));
}
