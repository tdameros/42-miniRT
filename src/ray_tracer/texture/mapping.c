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
static t_vector3f	get_texture_at(const t_object *object, t_vector2f uv);

static t_vector3f	get_interpolate_pattern(t_vector2f uv, const t_object *object);



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
	(void) get_interpolate_pattern;
	if (object->material.is_texture == true)
		return (get_texture_at(object, uv));
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
//	if (hit_position.x < 0)
//		hit_position.x = -hit_position.x;
//	if (hit_position.z < 0)
//		hit_position.z = -hit_position.z;
	float	u = fmodf(hit_position.x, 1);
	float	v = fmodf(hit_position.z, 1);
	if (u < 0)
		u += 1;
	if (v < 0)
		v += 1;
//	const float	u = hit_position.x;
//	const float	v = hit_position.z;

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

static t_vector3f	get_texture_at(const t_object *object, t_vector2f uv)
{
	uv.y = 1 - uv.y;
	uv.x = 1 - uv.x;
	int x = roundf(uv.x * (float)(object->material.texture.width - 1));
	int y = roundf(uv.y * (float)(object->material.texture.height - 1));
	t_vector3f	pixel = object->material.texture.pixels[y * object->material.texture.width + x];
	return (pixel);
}

static t_vector3f get_interpolate_pattern(t_vector2f uv, const t_object *object)
{
	float u_frac = uv.x - floorf(uv.x);
	float v_frac = uv.y - floorf(uv.y);

//	int x1 = floorf(uv.x * (object->material.checked_pattern_size.x - 1));
//	int x2 = x1 + 1;
//	int y1 = floorf(uv.y * (object->material.checked_pattern_size.y - 1));
//	int y2 = y1 + 1;

// Obtention des valeurs des pixels adjacents à interpoler
	t_vector3f value_A = get_checked_pattern_at(vector2f_create(u_frac, v_frac), object);
	t_vector3f value_B = get_checked_pattern_at(vector2f_create(u_frac + 1, v_frac), object);
	t_vector3f value_C = get_checked_pattern_at(vector2f_create(u_frac, v_frac + 1), object);
	t_vector3f value_D = get_checked_pattern_at(vector2f_create(u_frac + 1, v_frac + 1), object);

// Interpolation bilinéaire
	t_vector3f interpolated_value = vector3f_create(0, 0, 0);
	interpolated_value = vector3f_add(interpolated_value, vector3f_multiply(value_A, (1 - u_frac) * (1 - v_frac)));
	interpolated_value = vector3f_add(interpolated_value, vector3f_multiply(value_B, u_frac * (1 - v_frac)));
	interpolated_value = vector3f_add(interpolated_value, vector3f_multiply(value_C, (1 - u_frac) * v_frac));
	interpolated_value = vector3f_add(interpolated_value, vector3f_multiply(value_D, u_frac * v_frac));

	return (interpolated_value);
}