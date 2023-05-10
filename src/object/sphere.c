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

#include "object.h"
#include "ray_tracer/ray.h"

t_object	sphere_create(t_vector3 origin, double radius, t_vector3 albedo)
{
	t_object	sphere;

	sphere.position = origin;
	sphere.radius = radius;
	sphere.albedo = albedo;
	return (sphere);
}

double	hit_sphere(t_ray ray, t_object sphere)
{
	const t_vector3	origin = vector3_subtract(ray.origin, sphere.position);
	const double	a = vector3_dot(ray.direction, ray.direction);
	const double	b = 2 * vector3_dot(origin, ray.direction);
	const double	c = vector3_dot(origin, origin)
		- sphere.radius * sphere.radius;
	const double	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (-1);
	return ((-b - sqrt(discriminant)) / (a * 2));
}
