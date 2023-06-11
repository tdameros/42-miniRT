/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:20:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/15 17:20:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "math/vector.h"
#include "ray_tracer/rays.h"

t_object	plane_create(t_vector3f position, t_vector3f normal,
						t_vector3f albedo)
{
	t_object	plane;

	plane.type = PLANE;
	plane.position = position;
	plane.normal = normal;
	plane.albedo = albedo;
	return (plane);
}


t_hit	hit_plane(t_ray ray, t_object plane, float distance)
{
	t_hit		hit;

	hit.distance = distance;
	if (hit.distance < 0)
	{
		hit.hit = false;
		return (hit);
	}
	hit.position = ray_at(ray, hit.distance);
	hit.normal = vector3f_unit(plane.normal);
	hit.object = plane;
	hit.ray = ray;
	hit.hit = true;
	return (hit);
}

float	calculate_plane_distance(t_ray ray, t_object plane)
{
	const float	scalar_product = vector3f_dot(ray.direction, plane.normal);
	const float	d = -vector3f_dot(plane.normal, plane.position);
	float		t;

	if (scalar_product == 0)
		return (-1);
	t = (-vector3f_dot(plane.normal, ray.origin) - d)
		/ vector3f_dot(plane.normal, ray.direction);
	return (t);
}
