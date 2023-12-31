/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 01:05:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/09 01:05:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "math/quaternion.h"

void	plane_move(t_object *plane, const t_vector3f movement_axis,
					const float distance)
{
	plane->position = vector3f_add(plane->position,
			vector3f_multiply(movement_axis, distance));
	plane_calculate_cache(plane);
}

void	plane_rotate(t_object *plane, const t_vector3f rotation_degrees)
{
	plane->axis_degrees = clamp_rotation_degrees(rotation_degrees);
	plane->axis = get_normal_from_rotation(plane->axis_degrees);
	plane_calculate_cache(plane);
}

void	plane_set_position(t_object *plane, const t_vector3f position)
{
	plane->position = position;
	plane_calculate_cache(plane);
}
