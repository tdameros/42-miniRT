/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:23:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:23:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "float.h"

#include "object.h"

static void	calculate_bounding_box_using_min_max(t_object *mesh_object,
				t_vector3f min, t_vector3f max);

void	mesh_calculate_bounding_box(t_object *mesh_object)
{
	t_vector3f	min;
	t_vector3f	max;
	size_t		i;

	min = (t_vector3f){FLT_MAX, FLT_MAX, FLT_MAX};
	max = (t_vector3f){-FLT_MAX, -FLT_MAX, -FLT_MAX};
	i = 0;
	while (i < mesh_object->mesh.faces.length)
	{
		min = vector3f_min(min, mesh_get_vertex_from_face(mesh_object, i, 0));
		min = vector3f_min(min, mesh_get_vertex_from_face(mesh_object, i, 1));
		min = vector3f_min(min, mesh_get_vertex_from_face(mesh_object, i, 2));
		max = vector3f_max(max, mesh_get_vertex_from_face(mesh_object, i, 0));
		max = vector3f_max(max, mesh_get_vertex_from_face(mesh_object, i, 1));
		max = vector3f_max(max, mesh_get_vertex_from_face(mesh_object, i, 2));
		i++;
	}
	calculate_bounding_box_using_min_max(mesh_object, min, max);
}

static void	calculate_bounding_box_using_min_max(t_object *mesh_object,
												t_vector3f min, t_vector3f max)
{
	mesh_object->bounding_box.aabb_min = min;
	mesh_object->bounding_box.aabb_max = max;
	mesh_object->bounding_box.top_face[0] = (t_vector3f){max.x, max.y, min.z};
	mesh_object->bounding_box.top_face[1] = max;
	mesh_object->bounding_box.top_face[2] = (t_vector3f){min.x, max.y, max.z};
	mesh_object->bounding_box.top_face[3] = (t_vector3f){min.x, max.y, min.z};
	mesh_object->bounding_box.bottom_face[0] = (t_vector3f){max.x,
		min.y, min.z};
	mesh_object->bounding_box.bottom_face[1] = (t_vector3f){max.x,
		min.y, max.z};
	mesh_object->bounding_box.bottom_face[2] = (t_vector3f){min.x,
		min.y, max.z};
	mesh_object->bounding_box.bottom_face[3] = min;
}
