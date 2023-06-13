/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:20:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/15 17:20:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "math/vector.h"

t_object	plane_create(t_vector3f position, t_vector3f normal, t_vector3f albedo)
{
	t_object	plane;

	plane.type = PLANE;
	plane.position = position;
	plane.normal = normal;
	plane.albedo = albedo;
	plane.d = -vector3f_dot(normal, position);
	return (plane);
}

float	hit_plane(t_ray ray, t_object plane)
{
	const float	scalar_product = vector3f_dot(ray.direction, plane.normal);
	float		t;

	if (scalar_product == 0)
		return (-1);
	t = (-vector3f_dot(plane.normal, ray.origin) - plane.d) / vector3f_dot(plane.normal, ray.direction);
	return (t);
}
