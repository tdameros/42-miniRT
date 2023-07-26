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

static t_vector3f	get_texture_at(const t_object *object,
						const enum e_hit_context context,
						const t_vector2f uv);
static	t_vector2f	get_uv_scale_checker_board_size(const t_object *object,
						const enum e_hit_context context,
						const t_vector2f uv);
static t_vector3f	get_checked_pattern_at(const t_object *object,
						const enum e_hit_context context,
						const t_vector2f uv);

t_vector3f	get_texture_color(t_hit hit, const t_object *object)
{
	t_vector2f			uv;
	enum e_hit_context	texture_context;

	if (hit.context == CAP1 || hit.context == CAP2)
		uv = calculate_cap_map(hit.position, object);
	else
		uv = calculate_object_map(hit.position, object);

	texture_context = hit.context;
	if (object->material.texture.outline_type == PPM_TEXTURE
		&& texture_context == OUTLINE)
		return (get_texture_at(object, texture_context, uv));
	if (object->material.texture.cap_type == PPM_TEXTURE
		&& (texture_context == CAP1 || texture_context == CAP2))
		return (get_texture_at(object, texture_context, uv));
	return (get_checked_pattern_at(object, texture_context, uv));
}

static t_vector3f	get_checked_pattern_at(const t_object *object,
											const enum e_hit_context context,
											const t_vector2f uv)
{
	const t_vector2f	scaled_uv = get_uv_scale_checker_board_size(object,
			context, uv);

	if (fmodf(scaled_uv.x + scaled_uv.y, 2) == 0)
		return (object->material.albedo);
	else
	{
		if (context == OUTLINE)
			return (object->material.texture.outline_checkerboard.albedo);
		else
			return (object->material.texture.cap_checkerboard.albedo);
	}
}

static	t_vector2f	get_uv_scale_checker_board_size(const t_object *object,
											const enum e_hit_context context,
											const t_vector2f uv)
{
	t_vector2f	scaled_uv;

	if (context == OUTLINE)
	{
		scaled_uv.x = floorf(uv.x
				* object->material.texture.outline_checkerboard.size.x);
		scaled_uv.y = floorf(uv.y
				* object->material.texture.outline_checkerboard.size.y);
	}
	else
	{
		scaled_uv.x = floorf(uv.x
				* object->material.texture.cap_checkerboard.size.x);
		scaled_uv.y = floorf(uv.y
				* object->material.texture.cap_checkerboard.size.y);
	}
	return (scaled_uv);
}

static t_vector3f	get_texture_at(const t_object *object,
									const enum e_hit_context context,
									const t_vector2f uv)
{
	t_vector3f	reverse_uv;
	int			x;
	int			y;

	reverse_uv.x = 1 - uv.x;
	reverse_uv.y = 1 - uv.y;
	if (context == OUTLINE)
	{
		x = roundf(uv.x
				* (float)(object->material.texture.outline_texture.width - 1));
		y = roundf(uv.y
				* (float)(object->material.texture.outline_texture.height - 1));
	}
	else
	{
		x = roundf(uv.x * (float)(object->material.texture.cap_texture.width
					- 1));
		y = roundf(uv.y * (float)(object->material.texture.cap_texture.height
					- 1));
	}
	if (context == OUTLINE)
		return (object->material.texture.outline_texture.pixels[y
				* object->material.texture.outline_texture.width + x]);
	else
		return (object->material.texture.cap_texture.pixels[y
				* object->material.texture.cap_texture.width + x]);
}
