/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:57:44 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/06 17:57:45 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/vector.h"
#include "ray_tracer/rays.h"

t_ray	ray_create(const t_vector3f origin, const t_vector3f direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_vector3f	ray_at(const t_ray *ray, const float t)
{
	return (vector3f_add(ray->origin, vector3f_multiply(ray->direction, t)));
}

t_vector3f	reflect(const t_vector3f i, const t_vector3f n)
{
	return (vector3f_subtract(i, vector3f_multiply(n,
				vector3f_dot(n, i) * 2.0f)));
}
