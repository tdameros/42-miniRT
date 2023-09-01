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

#include "ray_tracer/rays.h"

static float calculate_face_distance(const t_ray *ray, const t_mesh *mesh,
									 const t_mesh_face *face);
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

#include <stdio.h>
void	vector2i_print(t_vector2i v)
{
	printf("Vector2i => x: %d y: %d\n", v.x, v.y);
}
t_hit	calculate_mesh_distance(const t_ray *ray, const t_object *mesh)
{
	float		t;
	t_hit		test;
	t_hit		hit;
	size_t		i;

	hit.distance = -1;
	hit.context = OUTLINE;
	i = 0;
	t = -1;
	while (i < mesh->mesh.faces.length)
	{
		t_vector3f normal = mesh->mesh.normals.data[mesh->mesh.faces.data[i].vertex_a.y - 1];
		test.distance = calculate_face_distance(ray, &mesh->mesh, &mesh->mesh.faces.data[i]);
		if (test.distance > 0.f && (t == -1.f || test.distance < t))
		{
			t = test.distance;
			hit.normal = normal;
		}
		i++;
	}
	if (t > 0)
		hit.distance = t;
	return (hit);
}

#include "float.h"
static float calculate_face_distance(const t_ray *ray, const t_mesh *mesh,
							  const t_mesh_face *face)
{
	float		t;

	t_vector3f	vertex_a = mesh->vertex.data[face->vertex_a.x - 1];
	t_vector3f	vertex_b = mesh->vertex.data[face->vertex_b.x - 1];
	t_vector3f	vertex_c = mesh->vertex.data[face->vertex_c.x - 1];
	t_vector3f edge_1 = vector3f_subtract(vertex_b, vertex_a);
	t_vector3f edge_2 = vector3f_subtract(vertex_c, vertex_a);
	t_vector3f h = vector3f_cross(ray->direction, edge_2);
	float a = vector3f_dot(edge_1, h);

	if (ft_is_equalsf(a, 0, FLT_EPSILON))
		return (-1);
	float f = 1.0f / a;
	t_vector3f s = vector3f_subtract(ray->origin, vertex_a);
	float u = f * vector3f_dot(s, h);

	if (u < 0.f || u > 1.f)
		return (-1);

	t_vector3f q = vector3f_cross(s, edge_1);
	float v = f * vector3f_dot(ray->direction, q);

	if (v < 0.f || u + v > 1.f)
		return (-1);

	t = f * vector3f_dot(edge_2, q);
	return (t);
}