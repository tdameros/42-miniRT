/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:11:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/03 18:11:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/rays.h"
#include "math/equation.h"

static t_vector3f	calculate_cone_normal(const t_ray *ray,
						const t_object *cone,
						const t_hit hit_distance);

t_hit	hit_cone(const t_ray *ray, const t_object *cone,
				const t_hit hit_distance)
{
	t_hit	hit;

	if (hit_distance.distance < 0.f)
	{
		hit.hit = false;
		return (hit);
	}
	hit.distance = hit_distance.distance;
	hit.context = hit_distance.context;
	hit.hit = true;
	hit.position = ray_at(ray, hit.distance);
	hit.normal = calculate_cone_normal(ray, cone, hit_distance);
	if (vector3f_dot(hit.normal, ray->direction) > 0)
		hit.normal = vector3f_multiply(hit.normal, -1);
	hit.object = cone;
	hit.ray = *ray;
	// TODO : get cone textures
	hit.albedo = cone->material.albedo;
	hit.shade_normal = hit.normal;
	return (hit);
}

static t_vector3f	calculate_cone_normal(const t_ray *ray,
										const t_object *cone,
										const t_hit hit_distance)
{
	if (hit_distance.context == OUTLINE)
		return (calculate_outline_cone_normal(ray, cone,
				hit_distance.distance));
	return (cone->cache.cone.cap_normal);
}

/**
 * https://physique.cmaisonneuve.qc.ca/svezina/nyc/note_nyc/
 * NYC_CHAP_6_IMPRIMABLE_4.pdf
 */
t_hit	calculate_cone_distance(const t_ray *ray, const t_object *cone)
{
	const float	distance_outline = calculate_outline_cone_distance(ray, cone);
	const float	distance_cap = calculate_cap_cone_distance(ray, cone);
	float		near_distance;
	t_hit		hit;

	hit.distance = -1;
	hit.context = OUTLINE;
	if (!is_in_outline_cone(ray, cone, distance_outline))
	{
		hit.context = CAP1;
		hit.distance = distance_cap;
		return (hit);
	}
	near_distance = ft_minf_positive(distance_outline, distance_cap);
	hit.distance = near_distance;
	if (near_distance == distance_outline)
		hit.context = OUTLINE;
	else
		hit.context = CAP1;
	return (hit);
}
