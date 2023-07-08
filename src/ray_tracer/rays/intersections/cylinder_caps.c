/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/08 16:21:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/rays.h"

static float	calculate_cylinder_cap1_distance(const t_ray *ray,
					const t_object *cylinder);
static float	calculate_cylinder_cap2_distance(const t_ray *ray,
					const t_object *cylinder);

t_hit	calculate_cylinder_caps_distance(const t_ray *ray,
										const t_object *cylinder)
{
	const float	cap1_distance = calculate_cylinder_cap1_distance(ray, cylinder);
	const float	cap2_distance = calculate_cylinder_cap2_distance(ray, cylinder);
	t_hit		hit;

	hit.distance = ft_minf_positive(cap1_distance, cap2_distance);
	if (hit.distance == cap1_distance)
		hit.context = CAP1;
	else
		hit.context = CAP2;
	return (hit);
}

static float	calculate_cylinder_cap1_distance(const t_ray *ray,
												const t_object *cylinder)
{
	const float	scalar_product = vector3f_dot(ray->direction,
			cylinder->cache.cylinder.cap1_normal);
	float		t;
	t_vector3f	hit_position;
	float		hit_radius;

	if (scalar_product == 0)
		return (-1);
	t = (-vector3f_dot(cylinder->cache.cylinder.cap1_normal, ray->origin) \
		- cylinder->cache.cylinder.cap1_d) \
		/ vector3f_dot(cylinder->cache.cylinder.cap1_normal, ray->direction);
	hit_position = ray_at(ray, t);
	hit_radius = vector3f_length(vector3f_subtract(hit_position,
				cylinder->cache.cylinder.endpoint1));
	if (hit_radius <= cylinder->radius)
		return (t);
	return (-1);
}

static float	calculate_cylinder_cap2_distance(const t_ray *ray,
												const t_object *cylinder)
{
	const float	scalar_product = vector3f_dot(ray->direction,
			cylinder->cache.cylinder.cap2_normal);
	float		t;
	t_vector3f	hit_position;
	float		hit_radius;

	if (scalar_product == 0)
		return (-1);
	t = (-vector3f_dot(cylinder->cache.cylinder.cap2_normal, ray->origin) \
		- cylinder->cache.cylinder.cap2_d) \
		/ vector3f_dot(cylinder->cache.cylinder.cap2_normal, ray->direction);
	hit_position = ray_at(ray, t);
	hit_radius = vector3f_length(vector3f_subtract(hit_position,
				cylinder->cache.cylinder.endpoint2));
	if (hit_radius <= cylinder->radius)
		return (t);
	return (-1);
}
