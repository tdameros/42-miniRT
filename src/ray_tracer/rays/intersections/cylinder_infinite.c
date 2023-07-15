/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_infinite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:09:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/16 21:09:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/rays.h"
#include "math/equation.h"
#include "ray_tracer/texture.h"

t_hit	hit_infinite_cylinder(const t_ray *ray, const t_object *cylinder,
								const t_hit hit_distance)
{
	t_hit		hit;

	hit.distance = hit_distance.distance;
	if (hit.distance < 0)
	{
		hit.hit = false;
		return (hit);
	}
	hit.position = ray_at(ray, hit.distance);
	hit.normal = calculate_infinite_cylinder_normal(ray, cylinder,
			hit_distance.distance);
	hit.object = cylinder;
	hit.ray = *ray;
	hit.hit = true;
	hit.albedo = get_texture_color(hit, cylinder);
	return (hit);
}

t_vector3f	calculate_infinite_cylinder_normal(const t_ray *ray,
											const t_object *cylinder,
											const float distance)
{
	t_vector3f	ra;
	t_vector3f	va;

	ra = vector3f_cross(cylinder->axe, vector3f_subtract(ray->origin,
				cylinder->position));
	ra = vector3f_cross(ra, cylinder->axe);
	va = vector3f_cross(cylinder->axe, ray->direction);
	va = vector3f_multiply(vector3f_cross(va, cylinder->axe), distance);
	return (vector3f_unit(vector3f_add(ra, va)));
}

t_hit	calculate_inf_cylinder_distance(const t_ray *ray,
										const t_object *cylinder)
{
	t_vector3f			ra0;
	t_vector3f			va;
	t_quadf_equation	equation;
	t_hit				hit;

	ra0 = vector3f_cross(cylinder->axe, vector3f_subtract(ray->origin,
				cylinder->position));
	ra0 = vector3f_cross(ra0, cylinder->axe);

	va = vector3f_cross(cylinder->axe, ray->direction);
	va = vector3f_cross(va, cylinder->axe);

	equation.a = vector3f_dot(va, va);
	equation.b = 2 * vector3f_dot(ra0, va);
	equation.c = vector3f_dot(ra0, ra0) - cylinder->radius * cylinder->radius;
	hit.distance = -1;
	hit.context = OUTLINE;
	if (!solve_quadratic_equation(&equation))
		return (hit);
	hit.distance = ft_minf_positive(equation.s1, equation.s2);
	return (hit);
}
