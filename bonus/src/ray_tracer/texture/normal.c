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
#include "math/matrix.h"
#include "object.h"
#include "ray_tracer/rays.h"
#include "ray_tracer/texture.h"

static t_vector3f	get_tangente_space_normal(const t_vector3f world_normal,
						const t_vector3f map_normal);
static t_vector3f	get_normal_in_map(const t_vector2f uv,
						const t_surface surface);

t_vector3f	calculate_normal_perturbation(t_hit hit, const t_object *object)
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
	return (get_tangente_space_normal(hit.normal,
			get_normal_in_map(uv, surface)));
}

static t_vector3f	get_tangente_space_normal(const t_vector3f world_normal,
											const t_vector3f map_normal)
{
	t_vector3f	tangent;
	t_vector3f	bitangent;
	t_matrix3	tbn;

	tangent = vector3f_cross(world_normal, (t_vector3f){0.f, 1.f, 0.f});
	if (vector3f_length(tangent) == 0)
		tangent = vector3f_cross(world_normal, (t_vector3f){0.f, 0.f, 1.f});
	tangent = vector3f_unit(tangent);
	bitangent = vector3f_unit(vector3f_cross(world_normal, tangent));
	tbn.size = 3;
	tbn.matrix[0][0] = tangent.x;
	tbn.matrix[1][0] = tangent.y;
	tbn.matrix[2][0] = tangent.z;
	tbn.matrix[0][1] = bitangent.x;
	tbn.matrix[1][1] = bitangent.y;
	tbn.matrix[2][1] = bitangent.z;
	tbn.matrix[0][2] = world_normal.x;
	tbn.matrix[1][2] = world_normal.y;
	tbn.matrix[2][2] = world_normal.z;
	return (vector3f_unit(matrix3_dot_vector3(tbn, map_normal)));
}

static t_vector3f	get_normal_in_map(const t_vector2f uv,
									const t_surface surface)
{
	t_vector3f	reverse_uv;
	int			x;
	int			y;
	t_vector3f	normal;

	reverse_uv.x = 1 - uv.x;
	reverse_uv.y = 1 - uv.y;
	x = (int) roundf(uv.x * (float)(surface.normals_map.width - 1));
	y = (int) roundf(uv.y * (float)(surface.normals_map.height - 1));
	x = ft_clamp(x, 0, surface.normals_map.width - 1);
	y = ft_clamp(y, 0, surface.normals_map.height - 1);
	normal = surface.normals_map.pixels[y * surface.normals_map.width + x];
	normal = vector3f_subtract(vector3f_multiply(normal, 2),
			vector3f_create(1, 1, 1));
	return (normal);
}
