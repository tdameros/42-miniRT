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

t_vector3f	calculate_outline_cone_normal(const t_ray *ray,
											const t_object *cone,
											const float distance);
float	calculate_outline_cone_distance(const t_ray *ray, const t_object *cone);
bool	is_in_outline_cone(const t_ray *ray, const t_object *cone, const float distance);
t_vector3f	calculate_cone_normal(const t_ray *ray, const t_object *cone,
									const float distance);

t_hit	hit_cone(const t_ray *ray, const t_object *cone, const float distance)
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
	hit.normal = calculate_cone_normal(ray, cone, distance);
	if (vector3f_dot(hit.normal, ray->direction) > 0)
		hit.normal = vector3f_multiply(hit.normal, -1);
	hit.object = cone;
	hit.ray = *ray;
//	if (hit.object->material.is_checked_pattern)
//		hit.albedo = get_checked_pattern(hit, cone);
//	else
	hit.albedo = cone->material.albedo;
	return (hit);

}

float	calculate_cone_distance(const t_ray *ray, const t_object *cone)
{
	const float	distance_outline = calculate_outline_cone_distance(ray, cone);
	const float	distance_cap = calculate_cap_cone_distance(ray, cone);

	if (distance_outline < 0)
		return (-1);
	if (!is_in_outline_cone(ray, cone, distance_outline))
		return (distance_cap);
	return (ft_minf_positive(distance_outline, distance_cap));
}

t_vector3f	calculate_cone_normal(const t_ray *ray, const t_object *cone,
									const float distance)
{
	const float	distance_outline = calculate_outline_cone_distance(ray, cone);

	if (distance == distance_outline)
		return (calculate_outline_cone_normal(ray, cone, distance));
	return (vector3f_multiply(cone->axe, -1));
}
