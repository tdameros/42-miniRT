/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:14:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/19 15:14:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "object.h"
#include "math/vector.h"
#include "ray_tracer/texture.h"

t_vector2f	calculate_object_map(const t_vector3f hit_position,
								const t_object *object)
{
	if (object->type == SPHERE)
		return (calculate_spherical_map(hit_position, object));
	else if (object->type == CYLINDER || object->type == CYLINDER_INF)
		return (calculate_cylindrical_map(hit_position, object));
	else if (object->type == PLANE)
		return (calculate_planar_map(hit_position, object));
	return ((t_vector2f){0.f, 0.f});
}

t_vector2f	calculate_spherical_map(const t_vector3f hit_position,
									const t_object *sphere)
{
	const t_vector3f	position = vector3f_subtract(hit_position,
			sphere->position);
	const float			theta = atan2f(position.x, position.z);
	const float			phi = acosf(position.y / sphere->radius);
	const float			raw_u = (float)(theta / (2.f * M_PI));

	return (vector2f_create(1.f - (raw_u + 0.5f), (float)(1.f - phi / M_PI)));
}

t_vector2f	calculate_cylindrical_map(const t_vector3f hit_position,
										const t_object *cylinder)
{
	const t_vector3f	position = vector3f_subtract(hit_position,
			cylinder->position);
	const float			theta = atan2f(position.x, position.z);
	const float			raw_u = theta / (2 * M_PI);
	const float			u = 1 - (raw_u + 0.5f);
	const float			v = fmodf(position.y, 1);

	return (vector2f_create(u, v));
}

t_vector2f	calculate_planar_map(const t_vector3f hit_position,
									const t_object *plane)
{
	float	u;
	float	v;

	(void) plane;
	u = fmodf(hit_position.x, 1);
	v = fmodf(hit_position.z, 1);
	if (u < 0)
		u += 1;
	if (v < 0)
		v += 1;
	return (vector2f_create(u, v));
}

