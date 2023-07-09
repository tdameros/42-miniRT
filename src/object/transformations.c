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
}

void	object_rotate(t_object *object, const t_vector3f rotation_axis,
						const float distance)
{
	if (object->type == CONE)
		cone_rotate(object, rotation_axis, distance);
	else if (object->type == CYLINDER || object->type == CYLINDER_INF)
		cylinder_rotate(object, rotation_axis, distance);
	else if (object->type == PLANE)
		plane_rotate(object, rotation_axis, distance);
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