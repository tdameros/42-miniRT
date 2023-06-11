/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:43:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/07 15:43:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math/equation.h"

#include "object.h"
#include "ray_tracer/rays.h"

t_object	sphere_create(t_vector3f origin, float radius, t_vector3f albedo)
{
	t_object	sphere;

	sphere.type = SPHERE;
	sphere.position = origin;
	sphere.radius = radius;
	sphere.albedo = albedo;
	return (sphere);
}


t_hit	hit_sphere(t_ray ray, t_object sphere, float distance)
{
	t_hit		hit;

	hit.distance = distance;
	if (hit.distance < 0)
	{
		hit.hit = false;
		return (hit);
	}
	hit.position = ray_at(ray, hit.distance);
	hit.normal = vector3f_unit(vector3f_subtract(hit.position,
				sphere.position));
	hit.object = sphere;
	hit.ray = ray;
	hit.hit = true;
	return (hit);
}

float	calculate_sphere_distance(t_ray ray, t_object sphere)
{
	const t_vector3f	origin = vector3f_subtract(ray.origin, sphere.position);
	const float			a = vector3f_dot(ray.direction, ray.direction);
	const float			b = 2 * vector3f_dot(origin, ray.direction);
	const float			c = vector3f_dot(origin, origin)
		- sphere.radius * sphere.radius;
	float				quadratic_result[3];

	if (!solve_quadratic_equation(a, b, c, quadratic_result))
		return (-1);
	return (ft_minf_positive(quadratic_result[0], quadratic_result[1]));
}