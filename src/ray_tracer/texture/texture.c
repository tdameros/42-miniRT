/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:05:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/13 18:05:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "object.h"
#include "material.h"
#include "ray_tracer/texture.h"
#include "ray_tracer/rays.h"
#include <stdio.h>

static t_vector3f	get_texture_at(const t_object *object, t_vector2f uv);
static t_vector3f	get_checked_pattern_at(const t_object *object, const t_vector2f uv);

t_vector3f	get_texture_color(t_hit hit, const t_object *object)
{
	t_vector2f	uv;

	if (object->material.texture.type == NONE)
		return (object->material.albedo);
	if (object->type == SPHERE)
		uv = calculate_spherical_map(hit.position, object);
	else if (object->type == CYLINDER || object->type == CYLINDER_INF)
		uv = calculate_cylindrical_map(hit.position, object);
	else if (object->type == PLANE)
		uv = calculate_planar_map(hit.position, object);
	else
		uv = vector2f_create(0, 0);
	if (object->material.texture.type == PPM_TEXTURE)
		return (get_texture_at(object, uv));
	return (get_checked_pattern_at(object, uv));
}

static t_vector3f	get_checked_pattern_at(const t_object *object,
											const t_vector2f uv)
{
	const double	u2 = floorf(uv.x
			* object->material.texture.checker_board.width);
	const double	v2 = floorf(uv.y
			* object->material.texture.checker_board.height);

	if (fmodf((float)(u2 + v2), 2) == 0)
		return (object->material.albedo);
	else
		return (object->material.texture.checker_board.albedo);
}

static t_vector3f	get_texture_at(const t_object *object, t_vector2f uv)
{
	int	x;
	int	y;

	uv.y = 1 - uv.y;
	uv.x = 1 - uv.x;
	x = roundf(uv.x * (float)(object->material.texture.texture_file.width - 1));
	y = roundf(uv.y * (float)(object->material.texture.texture_file.height
				- 1));
	return (object->material.texture.texture_file.pixels[y
			* object->material.texture.texture_file.width + x]);
}
