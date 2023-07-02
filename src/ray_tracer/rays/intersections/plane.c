/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:13:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/16 21:13:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ray_tracer/rays.h"
#include "ray_tracer/mapping.h"

t_hit	hit_plane(const t_ray *ray, const t_object *plane, float distance)
{
	t_hit		hit;

	hit.distance = distance;
	if (hit.distance < 0)
	{
		hit.hit = false;
		return (hit);
	}
	hit.t = distance;
	hit.position = ray_at(ray, hit.distance);
	hit.normal = vector3f_unit(plane->normal);
//	if (vector3f_dot(ray->direction, hit.normal) < 0)
//		hit.normal = vector3f_multiply(hit.normal, -1);
	if (vector3f_dot(hit.normal, ray->direction) > 0)
		hit.normal = vector3f_multiply(hit.normal, -1);
	hit.object = plane;
	hit.ray = *ray;
	hit.hit = true;
	if (plane->material.is_checked_pattern)
		hit.albedo = get_checked_pattern(hit, plane);
	else
		hit.albedo = plane->material.albedo;
	return (hit);
}

float	calculate_plane_distance(const t_ray *ray, const t_object *plane)
{
	const float	scalar_product = vector3f_dot(ray->direction, plane->normal);
	const float	d = -vector3f_dot(plane->normal, plane->position);
	float		t;

	if (scalar_product == 0)
		return (-1);
	t = (-vector3f_dot(plane->normal, ray->origin) - d)
		/ vector3f_dot(plane->normal, ray->direction);
	return (t);
}
