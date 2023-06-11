/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_infinite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:08:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/10 14:08:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/rays.h"
#include "math/equation.h"

t_object	cylinder_infinite_create(t_vector3f origin, t_vector3f axe,
									float radius, t_vector3f albedo)
{
	t_object	cylinder;

	cylinder.type = CYLINDER_INF;
	cylinder.position = origin;
	cylinder.normal = axe;
	cylinder.radius = radius;
	cylinder.albedo = albedo;
	return (cylinder);
}


t_hit	hit_infinite_cylinder(t_ray ray, t_object cylinder, float distance)
{
	t_hit		hit;

	hit.distance = distance;
	if (hit.distance < 0)
	{
		hit.hit = false;
		return (hit);
	}
	hit.position = ray_at(ray, hit.distance);
	hit.normal = calculate_infinite_cylinder_normal(ray, cylinder, distance);
	hit.object = cylinder;
	hit.ray = ray;
	hit.hit = true;
	return (hit);
}

t_vector3f	calculate_infinite_cylinder_normal(t_ray ray, t_object cylinder,
		float distance)
{
	t_vector3f	ra;
	t_vector3f	va;

	ra = vector3f_cross(cylinder.normal, vector3f_subtract(ray.origin,
				cylinder.position));
	ra = vector3f_cross(ra, cylinder.normal);
	va = vector3f_cross(cylinder.normal, vector3f_unit(ray.direction));
	va = vector3f_multiply(vector3f_cross(va, cylinder.normal), distance);
	return (vector3f_unit(vector3f_add(ra, va)));
}

float	calculate_inf_cylinder_distance(t_ray ray,
		t_object cylinder)
{
	float		equation[3];
	float		result[2];
	t_vector3f	ra0;
	t_vector3f	va;

	ra0 = vector3f_cross(cylinder.normal, vector3f_subtract(ray.origin,
				cylinder.position));
	ra0 = vector3f_cross(ra0, cylinder.normal);

	va = vector3f_cross(cylinder.normal, vector3f_unit(ray.direction));
	va = vector3f_cross(va, cylinder.normal);

	equation[0] = vector3f_dot(va, va);
	equation[1] = 2 * vector3f_dot(ra0, va);
	equation[2] = vector3f_dot(ra0, ra0) - cylinder.radius * cylinder.radius;
	if (!solve_quadratic_equation(equation[0], equation[1], equation[2],
			result))
		return (-1);
	return (ft_minf_positive(result[0], result[1]));
}
