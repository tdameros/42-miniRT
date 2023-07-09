/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_infinite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:06:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/07 00:06:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/rays.h"
#include "math/vector.h"
#include "math/equation.h"

float	calculate_outline_cone_distance(const t_ray *ray, const t_object *cone)
{
	const t_vector3f	va = vector3f_cross(vector3f_cross(cone->axe,
				ray->direction), cone->axe);
	const float			vs = vector3f_dot(ray->direction, cone->axe);
	const t_vector3f	ra0 = vector3f_cross(vector3f_cross(cone->axe, \
		vector3f_subtract(ray->origin, cone->cache.cone.endpoint1)), cone->axe);
	const float			big_w = cone->height - vector3f_dot(vector3f_subtract(\
			ray->origin, cone->cache.cone.endpoint1), cone->axe);
	t_quadf_equation	equation;

	equation.a = vector3f_dot(va, va);
	equation.a -= (vs * vs) * cone->cache.cone.radius_divide_height;

	equation.b = vector3f_dot(vector3f_multiply(ra0, 2), va);
	equation.b += 2 * big_w * vs * cone->cache.cone.radius_divide_height;

	equation.c = vector3f_dot(ra0, ra0);
	equation.c -= (big_w * big_w) * cone->cache.cone.radius_divide_height;

	if (!solve_quadratic_equation(&equation))
		return (-1);
	if (equation.s1 >= 0 && !is_in_outline_cone(ray, cone, equation.s1))
		return (equation.s2);
	if (equation.s2 >= 0 && !is_in_outline_cone(ray, cone, equation.s2))
		return (equation.s1);
	return (ft_minf_positive(equation.s1, equation.s2));
}

t_vector3f	calculate_outline_cone_normal(const t_ray *ray,
											const t_object *cone,
											const float distance)
{
	const t_vector3f	point = ray_at(ray, distance);
	const t_vector3f	point_axe = vector3f_subtract(point,
			cone->cache.cone.endpoint2);
	const t_vector3f	point_to_axe = vector3f_subtract(cone->position, point);
	const t_vector3f	perpendicular_vector = vector3f_cross(\
							vector3f_cross(point_axe, point_to_axe), point_axe);

	return (vector3f_unit(perpendicular_vector));
}

bool	is_in_outline_cone(const t_ray *ray, const t_object *cone,
							const float distance)
{
	const t_vector3f	position = ray_at(ray, distance);
	const t_vector3f	endpoint1_position = vector3f_subtract(position,
			cone->cache.cone.endpoint1);
	const t_vector3f	endpoint2_position = vector3f_subtract(position,
			cone->cache.cone.endpoint2);

	return (vector3f_dot(endpoint1_position, cone->axe) > 0
		&& vector3f_dot(endpoint2_position, cone->axe) < 0);
}

float	calculate_cap_cone_distance(const t_ray *ray, const t_object *cone)
{
	const float			scalar_product = vector3f_dot(ray->direction,
			cone->cache.cone.cap_normal);
	float				t;
	t_vector3f			hit_position;
	float				hit_radius;

	if (scalar_product == 0)
		return (-1);
	t = (-vector3f_dot(cone->cache.cone.cap_normal, ray->origin) \
		- cone->cache.cone.cap_d)
		/ vector3f_dot(cone->cache.cone.cap_normal, ray->direction);
	hit_position = ray_at(ray, t);
	hit_radius = vector3f_length(vector3f_subtract(hit_position,
				cone->cache.cone.endpoint1));
	if (hit_radius <= cone->radius)
		return (t);
	return (-1);
}
