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
#include "ray_tracer/rays.h"

static t_vector2f	get_spherical_map(t_vector3f hit_position,
						const t_object *sphere);
static t_vector2f	get_cylindrical_map(t_vector3f hit_position,
						const t_object *cylinder);
static t_vector2f	get_planar_map(t_vector3f hit_position,
						const t_object *plane);
static t_vector3f	get_checked_pattern_at(t_vector2f uv,
						const t_object *object);

t_vector3f	get_checked_pattern(t_hit hit, const t_object *object)
{
	t_vector2f	uv;

	if (object->type == SPHERE)
		uv = get_spherical_map(hit.position, object);
	else if (object->type == CYLINDER)
		uv = get_cylindrical_map(hit.position, object);
	else if (object->type == PLANE)
		uv = get_planar_map(hit.position, object);
	else
		uv = vector2f_create(0, 0);
	return (get_checked_pattern_at(uv, object));
}

static t_vector2f	get_spherical_map(t_vector3f hit_position,
										const t_object *sphere)
{
	const t_vector3f	position = vector3f_subtract(hit_position,
			sphere->position);
	const float			theta = atan2f(position.x, position.z);
	const float			phi = acosf(position.y / sphere->radius);
	const float			raw_u = theta / (2 * M_PI);

	return (vector2f_create(1 - (raw_u + 0.5f), 1 - phi / M_PI));
}

#include <stdio.h>
static t_vector2f	get_cylindrical_map(t_vector3f hit_position,
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

static t_vector2f	get_planar_map(t_vector3f hit_position,
									const t_object *plane)
{
	(void) plane;
	const float	u = fmodf(hit_position.x, 1);
	const float	v = fmodf(hit_position.z, 1);

	return (vector2f_create(u, v));
}

static t_vector3f	get_checked_pattern_at(t_vector2f uv,
											const t_object *object)
{
	const double	u2 = floorf(uv.x * object->material.checked_pattern_size.x);
	const double	v2 = floorf(uv.y * object->material.checked_pattern_size.y);

	if (fmodf(u2 + v2, 2) == 0)
		return (object->material.albedo);
	else
		return (object->material.checked_pattern_albedo);
}


