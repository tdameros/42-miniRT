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

#include "ray_tracer/ray.h"
#include "math/vector.h"

t_ray	ray_create(t_vector3f origin, t_vector3f direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

// P(t) = A + tb
// A is ray origin point
// b is ray direction
// t is real number
// This fonction is equivalent of affine fonction in 3D f(x) = b + ax
t_vector3f	ray_at(t_ray ray, float t)
{
	return (vector3f_add(ray.origin, vector3f_multiply(ray.direction, t)));
}
