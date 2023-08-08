/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:20:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/08/06 23:20:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/rays.h"
#include "math/triangle.h"


t_hit	hit_triangle(const t_ray *ray, const t_object *triangle, const t_hit hit_distance)
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
	hit.normal = triangle->axis;
	if (vector3f_dot(hit.normal, ray->direction) > 0)
		hit.normal = vector3f_multiply(hit.normal, -1);
	hit.object = triangle;
	hit.ray = *ray;
	hit.hit = true;
	hit.albedo = triangle->material.albedo;
//	if (plane->material.texture.outline.has_normals_map)
//		hit.shade_normal = calculate_normal_perturbation(hit, plane);
//	else
	hit.shade_normal = hit.normal;
	return (hit);
}

t_hit	calculate_triangle_distance(const t_ray *ray, const t_object *triangle)
{
	const float	scalar_product = vector3f_dot(ray->direction, triangle->axis);
	float		t;
	t_hit		hit;

	hit.distance = -1;
	hit.context = OUTLINE;
	if (scalar_product == 0)
		return (hit);
	t = (-vector3f_dot(triangle->axis, ray->origin) - (-vector3f_dot(triangle->axis, triangle->vertex_a)))
		/ vector3f_dot(triangle->axis, ray->direction);
	t_vector3f point = ray_at(ray, t);
	if (point_is_in_triangle(point, triangle->vertex_a, triangle->vertex_b, triangle->vertex_c))
		hit.distance = t;
	else
		hit.distance = -1;
	return (hit);
}