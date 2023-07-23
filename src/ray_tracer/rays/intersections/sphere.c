/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:53:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/16 20:53:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "ray_tracer/rays.h"
#include "math/equation.h"
#include "ray_tracer/texture.h"

t_hit	hit_sphere(const t_ray *ray, const t_object *sphere,
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
	hit.normal = vector3f_unit(vector3f_subtract(hit.position,
				sphere->position));
	if (vector3f_dot(hit.normal, ray->direction) > 0)
		hit.normal = vector3f_multiply(hit.normal, -1);
	hit.object = sphere;
	hit.ray = *ray;
	hit.hit = true;
	hit.albedo = get_texture_color(hit, sphere);
	return (hit);
}

t_hit	calculate_sphere_distance(const t_ray *ray, const t_object *sphere)
{
	const t_vector3f	origin = vector3f_subtract(ray->origin,
			sphere->position);
	t_quadf_equation	equation;
	t_hit				hit;

	hit.distance = -1;
	hit.context = OUTLINE;
	equation.a = 1;
	equation.b = 2 * vector3f_dot(origin, ray->direction);
	equation.c = vector3f_dot(origin, origin)
		- sphere->cache.sphere.square_radius;
	if (!solve_quadratic_equation(&equation))
		return (hit);
	hit.distance = ft_minf_positive(equation.s1, equation.s2);
	return (hit);
}
