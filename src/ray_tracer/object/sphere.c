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

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "object.h"
#include "ray.h"

t_sphere	*sphere_create(t_vector3 origin, double radius, t_vector3 color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(*sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->origin = origin;
	sphere->radius = radius;
	sphere->color = color;
	return (sphere);
}

bool	hit_sphere(t_ray ray, t_sphere sphere)
{
	const t_vector3	origin = vector3_subtract(ray.origin, sphere.origin);
	const double	a = vector3_dot(ray.direction, ray.direction);
	const double	b = 2 * vector3_dot(origin, ray.direction);
	const double	c = vector3_dot(origin, origin)
		- sphere.radius * sphere.radius;

	return (b * b - 4 * a * c > 0);
}

double	get_hit_scalar_sphere(t_ray ray, t_sphere sphere)
{
	const t_vector3	origin = vector3_subtract(ray.origin, sphere.origin);
	const double	a = vector3_dot(ray.direction, ray.direction);
	const double	b = 2 * vector3_dot(origin, ray.direction);
	const double	c = vector3_dot(origin, origin)
		- sphere.radius * sphere.radius;

	return ((-b - sqrt(b * b - 4 * a * c)) / (2 * a));
}
