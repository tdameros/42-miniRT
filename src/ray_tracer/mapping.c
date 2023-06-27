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

static t_vector2f	get_spherical_map(t_vector3f hit_position,
						const t_object *sphere);
static t_vector2f	get_cylindrical_map(t_vector3f hit_position,
						const t_object *cylinder);
static t_vector2f	get_planar_map(t_vector3f hit_position,
						const t_object *plane);
static t_vector3f	get_checked_pattern_at(t_vector2f uv,
						const t_object *object);

t_vector3f	get_checked_pattern(t_vector3f hit_position, const t_object *object)
{
	t_vector2f	uv;

//	vector2f_print(get_planar_map(vector3f_create(0.25, 0.0f, 0.5f), object));
//	vector2f_print(get_planar_map(vector3f_create(0.25f, 0, -0.25f), object));
//	vector2f_print(get_planar_map(vector3f_create(0.25, 0.5, -0.25), object));
//	vector2f_print(get_planar_map(vector3f_create(1, 0, -1), object));
	if (object->type == SPHERE)
		uv = get_spherical_map(hit_position, object);
	else if (object->type == CYLINDER)
		uv = get_cylindrical_map(hit_position, object);
	else if (object->type == PLANE)
		uv = get_planar_map(hit_position, object);
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
//	const t_vector3f	position = hit_position;
	(void ) cylinder;
	const float			theta = atan2f(position.x, position.z);
	const float			raw_u = theta / (2 * M_PI);
	const float 		u = 1 - (raw_u + 0.5f);
	const float 		v = fmodf(position.y, 1);

//	printf("%f\n", fmodf(position.y, 1));
	return (vector2f_create(u, v));
}

static t_vector2f	get_planar_map(t_vector3f hit_position,
									const t_object *plane)
{
	(void) plane;
//	float	u = fmodf(hit_position.x, 1);
//	float	v = fmodf(hit_position.z, 1);

	float u = vector3f_dot()
//	if (hit_position.y != plane->position.y)
//	{
//		printf("Hit:\n");
//		vector3f_print(hit_position);
//		printf("Plane:\n");
//		vector3f_print(plane->position);
//	}
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


