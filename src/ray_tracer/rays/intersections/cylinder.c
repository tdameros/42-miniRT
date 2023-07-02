/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/16 21:01:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/vector.h"
#include "object.h"
#include "ray_tracer/rays.h"
#include "ray_tracer/mapping.h"

static float	calculate_cylinder_base_distance(const t_ray *ray, t_vector3f normal,
												 t_vector3f base, float radius);
static t_vector3f	calculate_cylinder_normal(const t_ray *ray, const t_object *cylinder,
											   float distance);

t_hit	hit_cylinder(const t_ray *ray, const t_object *cylinder, float distance)
{
	t_hit	hit;

	hit.distance = distance;
	if (hit.distance < 0)
	{
		hit.hit = false;
		return (hit);
	}
	hit.hit = true;
	hit.position = ray_at(ray, distance);
	hit.normal = vector3f_unit(calculate_cylinder_normal(ray, cylinder, distance));
	if (vector3f_dot(hit.normal, ray->direction) > 0)
		hit.normal = vector3f_multiply(hit.normal, -1);
	hit.object = cylinder;
	hit.ray = *ray;
	if (hit.object->material.is_checked_pattern)
		hit.albedo = get_checked_pattern(hit, cylinder);
	else
		hit.albedo = cylinder->material.albedo;
	return (hit);
}

static t_vector3f	calculate_cylinder_normal(const t_ray *ray, const t_object *cylinder,
											   float distance)
{
	const t_vector3f	endpoint_distance = vector3f_multiply(cylinder->normal,
															  cylinder->height / 2);
	const t_vector3f	endpoint1 = vector3f_add(cylinder->position,
												 endpoint_distance);
	const t_vector3f	endpoint2 = vector3f_subtract(cylinder->position,
													  endpoint_distance);
	const float			base_distance = ft_minf_positive(
			calculate_cylinder_base_distance(ray, cylinder->normal,
											 endpoint1, cylinder->radius),
			calculate_cylinder_base_distance(ray,
											 vector3f_multiply(cylinder->normal, -1),
											 endpoint2, cylinder->radius));
	float				top_base_distance;

	if (base_distance != distance)
		return (calculate_infinite_cylinder_normal(ray, cylinder, distance));
	top_base_distance = calculate_cylinder_base_distance(ray, cylinder->normal,
														 endpoint1, cylinder->radius);
	if (top_base_distance == distance)
		return (cylinder->normal);
	else
		return (vector3f_multiply(cylinder->normal, -1));
}

float	calculate_cylinder_distance(const t_ray *ray, const t_object *cylinder)
{
	const float			border_distance = calculate_inf_cylinder_distance(
			ray, cylinder);
	const t_vector3f	hit_position = ray_at(ray, border_distance);
	const t_vector3f	endpoint_distance = vector3f_multiply(cylinder->normal,
															  cylinder->height / 2);
	const t_vector3f	endpoint1 = vector3f_add(cylinder->position,
												 endpoint_distance);
	const t_vector3f	endpoint2 = vector3f_subtract(cylinder->position,
													  endpoint_distance);

	if (border_distance < 0)
		return (-1);
	if (vector3f_dot(vector3f_subtract(hit_position, endpoint1),
					 cylinder->normal) < 0
		&& vector3f_dot(vector3f_subtract(hit_position, endpoint2),
						cylinder->normal) > 0)
	{
		float near_base_d = ft_minf_positive(
				calculate_cylinder_base_distance(ray, cylinder->normal, endpoint1, cylinder->radius),
				calculate_cylinder_base_distance(ray, vector3f_multiply(cylinder->normal, -1), endpoint2, cylinder->radius));
		return (ft_minf_positive(border_distance, near_base_d));
	}
	return (ft_minf_positive(
			calculate_cylinder_base_distance(ray, cylinder->normal, endpoint1, cylinder->radius),
			calculate_cylinder_base_distance(ray, vector3f_multiply(cylinder->normal, -1), endpoint2, cylinder->radius)));
}

static float	calculate_cylinder_base_distance(const t_ray *ray, t_vector3f normal,
												 t_vector3f base, float radius)
{
	const float	d = -vector3f_dot(normal, base);
	const float	scalar_product = vector3f_dot(ray->direction, normal);
	float		t;
	t_vector3f	hit_position;
	float		hit_radius;

	if (scalar_product == 0)
		return (-1);
	t = (-vector3f_dot(normal, ray->origin) - d)
		/ vector3f_dot(normal, ray->direction);
	hit_position = ray_at(ray, t);
	hit_radius = vector3f_length(vector3f_subtract(hit_position, base));
	if (hit_radius <= radius)
		return (t);
	return (-1);
}
