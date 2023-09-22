/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:32:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/08 23:32:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "float.h"

#include "libft.h"

#include "object.h"
#include "math/quaternion.h"

void	mesh_object_move(t_object *mesh_object, const t_vector3f movement_axis,
			const float distance)
{
	if (mesh_object->type != MESH)
		return ;
	mesh_object->position = vector3f_add(mesh_object->position,
			vector3f_multiply(movement_axis, distance));
	mesh_object->cache.mesh.translation = create_translation_matrix(
			mesh_object->position);
	mesh_object_update_vertex(mesh_object);
}

void	mesh_object_set_position(t_object *mesh_object,
			const t_vector3f position)
{
	if (mesh_object->type != MESH)
		return ;
	mesh_object->position = position;
	mesh_object->cache.mesh.translation = create_translation_matrix(position);
	mesh_object_update_vertex(mesh_object);
}

void	mesh_object_set_rotation(t_object *mesh_object,
			const t_vector3f rotation_degrees)
{
	if (mesh_object->type != MESH)
		return ;
	mesh_object->axis_degrees = clamp_rotation_degrees(rotation_degrees);
	mesh_object->axis = mesh_object->axis_degrees;
	mesh_object->cache.mesh.rotation = create_rotation_matrix(
			mesh_object->axis_degrees);
	mesh_object_update_normals(mesh_object);
	mesh_object_update_vertex(mesh_object);
}

void	mesh_object_set_scale(t_object *mesh_object, t_vector3f scale)
{
	if (mesh_object->type != MESH)
		return ;
	if (ft_is_equalsf(scale.x, 0.f, FLT_EPSILON))
		scale.x = MESH_MINIMUM_SCALE;
	if (ft_is_equalsf(scale.y, 0.f, FLT_EPSILON))
		scale.y = MESH_MINIMUM_SCALE;
	if (ft_is_equalsf(scale.z, 0.f, FLT_EPSILON))
		scale.z = MESH_MINIMUM_SCALE;
	mesh_object->cache.mesh.scale_vector = scale;
	mesh_object->cache.mesh.scale = create_scale_matrix(scale);
	mesh_object_update_vertex(mesh_object);
}
