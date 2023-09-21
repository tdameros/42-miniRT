/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:02:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/19 17:02:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_vector3f	mesh_get_vertex_from_face(const t_object *mesh_object,
										size_t face_index, int vertex_index)
{
	if (vertex_index == 0)
		return (mesh_object->cache.mesh.vertex.data[mesh_object->mesh.faces.data[face_index].vertex_a.x - 1]);
	else if (vertex_index == 1)
		return (mesh_object->cache.mesh.vertex.data[mesh_object->mesh.faces.data[face_index].vertex_b.x - 1]);
	return (mesh_object->cache.mesh.vertex.data[mesh_object->mesh.faces.data[face_index].vertex_c.x - 1]);
}