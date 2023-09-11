/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                          :+:      :+:    :+:   */
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
						const t_surface surface,
						const t_vector2f uv);

static t_vector3f	get_checked_pattern_at(const t_object *object,
						const t_surface surface,
						const t_vector2f uv);

t_vector3f	get_texture_color(t_hit hit, const t_object *object)
{
	t_vector2f			uv;
	t_surface			surface;

	if (is_cap_context(hit.context))
	{
		surface = object->material.textures.cap;
		uv = calculate_cap_map(hit.position, object);
	}
	else
	{
		surface = object->material.textures.outline;
		uv = calculate_object_map(hit.position, object);
	}
	if (surface.texture_type == NONE)
		return (object->material.albedo);
	else if (surface.texture_type == CHECKERBOARD)
		return (get_checked_pattern_at(object, surface, uv));
	else
		return (get_texture_at(object, surface, uv));
}

static t_vector3f	get_checked_pattern_at(const t_object *object,
											const t_surface surface,
											const t_vector2f uv)
{
	t_vector2f	scaled_uv;

	scaled_uv.x = floorf(uv.x * surface.checkerboard.size.x);
	scaled_uv.y = floorf(uv.y * surface.checkerboard.size.y);
	if (fmodf(scaled_uv.x + scaled_uv.y, 2) == 0)
		return (object->material.albedo);
	else
		return (surface.checkerboard.albedo);
}

static t_vector3f	get_texture_at(const t_object *object,
									const t_surface surface,
									const t_vector2f uv)
{
	t_vector3f	reverse_uv;
	int			x;
	int			y;

	(void ) object;
	reverse_uv.x = 1 - uv.x;
	reverse_uv.y = 1 - uv.y;
	x = roundf(uv.x * (float)(surface.texture.width - 1));
	y = roundf(uv.y * (float)(surface.texture.height - 1));
	return (surface.texture.pixels[y * surface.texture.width + x]);
}
