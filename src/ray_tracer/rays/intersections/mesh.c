/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:22:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/08/08 18:22:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "float.h"

#include "ray_tracer/rays.h"

static float	calculate_face_distance(const t_ray *ray, const t_object *mesh,
					const t_mesh_face *face);
static float	calculate_moller_triangle_distance(const t_ray *ray, \
												const t_vector3f vertex[3], \
												const t_vector3f edge[2]);

t_hit	hit_mesh(const t_ray *ray, const t_object *mesh,
					const t_hit hit_distance)
{
	t_hit		hit;

	if (hit_distance.distance < 0.f)
	{
		hit.hit = false;
		return (hit);
	}
	hit.context = hit_distance.context;
	hit.distance = hit_distance.distance;
	hit.position = ray_at(ray, hit.distance);
	hit.normal = hit_distance.normal;
	if (vector3f_dot(hit.normal, ray->direction) > 0)
		hit.normal = vector3f_multiply(hit.normal, -1);
	hit.object = mesh;
	hit.ray = *ray;
	hit.hit = true;
	hit.albedo = mesh->material.albedo;
//	if (plane->material.texture.outline.has_normals_map)
//		hit.shade_normal = calculate_normal_perturbation(hit, plane);
//	else
	hit.shade_normal = hit.normal;
	return (hit);
}

t_hit	calculate_mesh_distance(const t_ray *ray, const t_object *mesh)
{
	t_hit		hit;
	size_t		i;
	float		t;
	float		distance;

	hit.distance = -1;
	hit.context = OUTLINE;
	i = 0;
	t = -1;
	while (i < mesh->mesh.faces.length)
	{
		distance = calculate_face_distance(ray, mesh,
				&mesh->mesh.faces.data[i]);
		if (distance > 0.f && (t == -1.f || distance < t))
		{
			t = distance;
			hit.normal = mesh->cache.mesh.normals.data[\
						mesh->mesh.faces.data[i].vertex_a.y - 1];
		}
		i++;
	}
	if (t > 0)
		hit.distance = t;
	return (hit);
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
