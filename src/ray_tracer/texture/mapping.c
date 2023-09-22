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
#include "float.h"

#include "math/vector.h"
#include "math/conversion.h"
#include "math/quaternion.h"
#include "math/modulo.h"
#include "object.h"
#include "ray_tracer/texture.h"

static t_vector2f	calculate_spherical_map(const t_vector3f hit_position,
						const t_object *sphere);

static t_vector2f	calculate_cylindrical_map(const t_vector3f hit_position,
						const t_object *cylinder);

static t_vector2f	calculate_planar_map(const t_vector3f hit_position,
						const t_object *plane);

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

static t_vector2f	calculate_spherical_map(const t_vector3f hit_position,
									const t_object *sphere)
{
	const t_vector3f	position = vector3f_subtract(hit_position,
			sphere->position);
	const float			theta = atan2f(position.x, position.z);
	const float			phi = acosf(position.y / sphere->radius);
	const float			raw_u = (float)(theta / (2.f * M_PI));

	return (vector2f_create((raw_u + 0.5f), (float)(phi / M_PI)));
}

static t_vector2f	calculate_cylindrical_map(const t_vector3f hit_position,
										const t_object *cylinder)
{
	t_vector3f	position;
	t_vector2f	uv;
	float		theta;
	float		raw_u;
	float		rotation_phi;

	position = vector3f_subtract(hit_position,
			cylinder->position);
	if (!ft_is_equalsf(cylinder->axis.y, 1.f, FLT_EPSILON))
	{
		rotation_phi = convert_radians_to_degrees(acosf(cylinder->axis.y));
		position = quaternionf_rotate_vector3f(-rotation_phi,
				vector3f_unit(vector3f_cross(vector3f_create(0, 1, 0), \
				cylinder->axis)), position);
	}
	theta = atan2f(position.x / cylinder->radius,
			position.z / cylinder->radius);
	raw_u = theta / (float)(2.f * M_PI);
	uv.x = 1.f - (raw_u + 0.5f);
	uv.y = (0.5f + position.y / cylinder->height);
	return (uv);
}

static t_vector2f	calculate_planar_map(const t_vector3f hit_position,
									const t_object *plane)
{
	t_vector3f	position;
	float		rotation_phi;
	float		u;
	float		v;

	position = vector3f_subtract(hit_position,
			plane->position);
	if (!ft_is_equalsf(plane->axis.y, 1.f, FLT_EPSILON))
	{
		rotation_phi = convert_radians_to_degrees(acosf(plane->axis.y));
		position = quaternionf_rotate_vector3f(-rotation_phi,
				vector3f_unit(vector3f_cross(vector3f_create(0, 1, 0), \
				plane->axis)), position);
	}
	u = modulof_positive(position.x, 1);
	v = modulof_positive(position.z, 1);
	return (vector2f_create(u, v));
}

t_vector2f	calculate_cap_map(const t_vector3f hit_position,
								const t_object *object)
{
	t_vector3f	position;
	float		rotation_phi;
	float		u;
	float		v;

	position = vector3f_subtract(hit_position, object->position);
	if (!ft_is_equalsf(object->axis.y, 1.f, FLT_EPSILON))
	{
		rotation_phi = convert_radians_to_degrees(acosf(object->axis.y));
		position = quaternionf_rotate_vector3f(-rotation_phi,
				vector3f_unit(vector3f_cross(vector3f_create(0, 1, 0), \
				object->axis)), position);
	}
	u = modulof_positive((position.x + object->radius)
			/ (object->radius * 2), 1);
	v = modulof_positive((position.z + object->radius)
			/ (object->radius * 2), 1);
	return (vector2f_create(u, v));
}
