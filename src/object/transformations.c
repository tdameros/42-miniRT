/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 01:29:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/09 01:29:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	object_move(t_object *object, const t_vector3f movement_axis,
					const float distance)
{
	if (object->type == CONE)
		cone_move(object, movement_axis, distance);
	else if (object->type == CYLINDER || object->type == CYLINDER_INF)
		cylinder_move(object, movement_axis, distance);
	else if (object->type == PLANE)
		plane_move(object, movement_axis, distance);
	else if (object->type == SPHERE)
		sphere_move(object, movement_axis, distance);
	else if (object->type == MESH)
		mesh_object_move(object, movement_axis, distance);
}

void	object_rotate(t_object *object, const t_vector3f rotation_axis,
						const float distance)
{
	object->axis_degrees = vector3f_add(object->axis_degrees,
			vector3f_multiply(rotation_axis, distance));
	if (object->axis_degrees.x >= 360.f)
		object->axis_degrees.x = (int)object->axis_degrees.x % 360;
	if (object->axis_degrees.y >= 360.f)
		object->axis_degrees.y = (int)object->axis_degrees.y % 360;
	if (object->axis_degrees.z >= 360.f)
		object->axis_degrees.z = (int)object->axis_degrees.z % 360;
	while (object->axis_degrees.x < 0.f)
		object->axis_degrees.x += 360.f;
	while (object->axis_degrees.y < 0.f)
		object->axis_degrees.y += 360.f;
	while (object->axis_degrees.z < 0.f)
		object->axis_degrees.z += 360.f;
	if (object->type == CONE)
		cone_rotate(object, rotation_axis, distance);
	else if (object->type == CYLINDER || object->type == CYLINDER_INF)
		cylinder_rotate(object, rotation_axis, distance);
	else if (object->type == PLANE)
		plane_rotate(object, rotation_axis, distance);
	else if (object->type == MESH)
		mesh_object_set_rotation(object, object->axis_degrees);
}

void	object_set_position(t_object *object, const t_vector3f position)
{
	if (object->type == CONE)
		cone_set_position(object, position);
	else if (object->type == CYLINDER || object->type == CYLINDER_INF)
		cylinder_set_position(object, position);
	else if (object->type == PLANE)
		plane_set_position(object, position);
	else if (object->type == SPHERE)
		sphere_set_position(object, position);
	else if (object->type == MESH)
		mesh_object_set_position(object, position);
}

void	object_set_height(t_object *object, const float height)
{
	if (object->type == CONE)
		cone_set_height(object, height);
	else if (object->type == CYLINDER)
		cylinder_set_height(object, height);
}

void	object_set_radius(t_object *object, const float radius)
{
	if (object->type == CONE)
		cone_set_radius(object, radius);
	else if (object->type == CYLINDER || object->type == CYLINDER_INF)
		cylinder_set_radius(object, radius);
	else if (object->type == SPHERE)
		sphere_set_radius(object, radius);
}
