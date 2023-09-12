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
			const t_vector3f rotation_axis)
{
	if (mesh_object->type != MESH)
		return ;
	mesh_object->axis = rotation_axis;
	mesh_object->cache.mesh.rotation = create_rotation_matrix(
			mesh_object->axis);
	mesh_object_update_normals(mesh_object);
	mesh_object_update_vertex(mesh_object);
}

void	mesh_object_set_scale(t_object *mesh_object, const t_vector3f scale)
{
	if (mesh_object->type != MESH)
		return ;
	mesh_object->cache.mesh.scale_vector = scale;
	mesh_object->cache.mesh.scale = create_scale_matrix(scale);
	mesh_object_update_vertex(mesh_object);
}
