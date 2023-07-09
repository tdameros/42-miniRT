/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 20:27:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/08 20:27:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/quaternion.h"
#include "object.h"

void	cone_move(t_object *cone, const t_vector3f movement_axis,
					const float distance)
{
	cone->position = vector3f_add(cone->position,
			vector3f_multiply(movement_axis, distance));
	cone_calculate_cache(cone);
}

void	cone_rotate(t_object *cone, const t_vector3f rotation_axis,
					const float degrees)
{
	cone->axe = vector3f_unit(quaternionf_rotate_vector3f(degrees,
				rotation_axis, cone->axe));
	cone_calculate_cache(cone);
}

void	cone_set_position(t_object *cone, const t_vector3f position)
{
	cone->position = position;
	cone_calculate_cache(cone);
}

void	cone_set_height(t_object *cone, const float height)
{
	cone->height = height;
	cone_calculate_cache(cone);
}

void	cone_set_radius(t_object *cone, const float radius)
{
	cone->radius = radius;
	cone_calculate_cache(cone);
}
