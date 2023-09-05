/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:27:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/29 18:27:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math/vector.h"
#include "object.h"
#include "ray_tracer/rays.h"
#include "ray_tracer/texture.h"

t_vector3f	get_normal_in_map(const t_vector2f uv, const t_surface surface);

t_vector3f	calculate_normal_perturbation(t_hit hit, const t_object *object)
{
	t_vector2f			uv;
	t_surface			surface;

	if (hit.context == CAP1 || hit.context == CAP2)
	{
		surface = object->material.textures.cap;
		uv = calculate_cap_map(hit.position, object);
	}
	else
	{
		surface = object->material.textures.outline;
		uv = calculate_object_map(hit.position, object);
	}
	return (vector3f_unit(vector3f_add(get_normal_in_map(uv, surface),
				hit.normal)));
}

t_vector3f	get_normal_in_map(const t_vector2f uv, const t_surface surface)
{
	t_vector3f	reverse_uv;
	int			x;
	int			y;
	t_vector3f	normal;

	reverse_uv.x = 1 - uv.x;
	reverse_uv.y = 1 - uv.y;
	x = roundf(uv.x * (float)(surface.normals_map.width - 1));
	y = roundf(uv.y * (float)(surface.normals_map.height - 1));
	normal = surface.normals_map.pixels[y * surface.normals_map.width + x];
	normal = vector3f_subtract(vector3f_multiply(normal, 2),
			vector3f_create(1, 1, 1));
	return (normal);
}
