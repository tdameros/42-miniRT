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
	t_hit			test;
	t_hit		hit;
	size_t		i;
	t_object	triangle;

	hit.distance = -1;
	hit.context = OUTLINE;
	i = 0;
	t = -1;
	while (i < mesh->mesh.faces.length)
	{
		t_vector3f	vertex_a = mesh->mesh.vertex.data[mesh->mesh.faces.data[i].vertex_a.x - 1];
		t_vector3f	vertex_b = mesh->mesh.vertex.data[mesh->mesh.faces.data[i].vertex_b.x - 1];
		t_vector3f	vertex_c = mesh->mesh.vertex.data[mesh->mesh.faces.data[i].vertex_c.x - 1];
		t_vector3f  normal = mesh->mesh.normals.data[mesh->mesh.faces.data[i].vertex_a.y - 1];
		triangle = triangle_create(vertex_a, vertex_b, vertex_c, normal,mesh->material);

//		exit(1);
		test = calculate_triangle_distance(ray, &triangle);
		if (test.distance > 0.f && (t == -1.f || test.distance < t))
		{
			t = test.distance;
			hit.normal = triangle.axis;
		}
		i++;
	}
	if (t > 0)
		hit.distance = t;
	return (hit);
}
