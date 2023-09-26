/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 01:29:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/26 15:57:49 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	object_move(t_object *object, const t_vector3f movement_axis,
					const float distance)
{
	if (object->type == CYLINDER)
		cylinder_move(object, movement_axis, distance);
	else if (object->type == PLANE)
		plane_move(object, movement_axis, distance);
	else if (object->type == SPHERE)
		sphere_move(object, movement_axis, distance);
}

void	object_rotate(t_object *object, const t_vector3f rotation_axis,
			const float degrees)
{
	object->axis_degrees = vector3f_add(object->axis_degrees,
			vector3f_multiply(rotation_axis, degrees));
	if (object->type == CYLINDER)
		cylinder_rotate(object, object->axis_degrees);
	else if (object->type == PLANE)
		plane_rotate(object, object->axis_degrees);
}

void	object_set_position(t_object *object, const t_vector3f position)
{
	if (object->type == CYLINDER)
		cylinder_set_position(object, position);
	else if (object->type == PLANE)
		plane_set_position(object, position);
	else if (object->type == SPHERE)
		sphere_set_position(object, position);
}

void	object_set_height(t_object *object, const float height)
{
	if (object->type == CYLINDER)
		cylinder_set_height(object, height);
}

void	object_set_radius(t_object *object, const float radius)
{
	if (object->type == CYLINDER)
		cylinder_set_radius(object, radius);
	else if (object->type == SPHERE)
		sphere_set_radius(object, radius);
}
