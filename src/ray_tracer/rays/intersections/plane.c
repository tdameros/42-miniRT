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
#include "ray_tracer/texture.h"

t_hit	hit_plane(const t_ray *ray, const t_object *plane, const t_hit hit_distance)
{
	t_hit		hit;

	hit.distance = hit_distance.distance;
	if (hit.distance < 0)
	{
		hit.hit = false;
		return (hit);
	}
	hit.t = hit_distance.distance;
	hit.position = ray_at(ray, hit.distance);
	hit.normal = plane->axe;
	if (vector3f_dot(hit.normal, ray->direction) > 0)
		hit.normal = vector3f_multiply(hit.normal, -1);
	hit.object = plane;
	hit.ray = *ray;
	hit.hit = true;
	hit.albedo = get_texture_color(hit, plane);
	return (hit);
}

t_hit	calculate_plane_distance(const t_ray *ray, const t_object *plane)
{
	const float	scalar_product = vector3f_dot(ray->direction, plane->axe);
	float		t;
	t_hit		hit;

	hit.distance = -1;
	hit.context = OUTLINE;
	if (scalar_product == 0)
		return (hit);
	t = (-vector3f_dot(plane->axe, ray->origin) - plane->cache.plane.d)
		/ vector3f_dot(plane->axe, ray->direction);
	hit.distance = t;
	return (hit);
}
