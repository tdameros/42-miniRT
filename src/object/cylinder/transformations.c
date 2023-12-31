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

void	cylinder_move(t_object *cylinder, const t_vector3f movement_axis,
						const float distance)
{
	cylinder->position = vector3f_add(cylinder->position,
			vector3f_multiply(movement_axis, distance));
	if (cylinder->type == CYLINDER)
		cylinder_calculate_cache(cylinder);
}

void	cylinder_rotate(t_object *cylinder, const t_vector3f rotation_degrees)
{
	cylinder->axis_degrees = clamp_rotation_degrees(rotation_degrees);
	cylinder->axis = get_normal_from_rotation(cylinder->axis_degrees);
	if (cylinder->type == CYLINDER)
		cylinder_calculate_cache(cylinder);
}

void	cylinder_set_position(t_object *cylinder, const t_vector3f position)
{
	cylinder->position = position;
	if (cylinder->type == CYLINDER)
		cylinder_calculate_cache(cylinder);
}

void	cylinder_set_height(t_object *cylinder, const float height)
{
	cylinder->height = height;
	cylinder_calculate_cache(cylinder);
}

void	cylinder_set_radius(t_object *cylinder, const float radius)
{
	cylinder->radius = radius;
}
