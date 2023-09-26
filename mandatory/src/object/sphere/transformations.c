/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 01:22:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/09 01:22:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	sphere_move(t_object *sphere, const t_vector3f movement_axis,
					const float distance)
{
	sphere->position = vector3f_add(sphere->position,
			vector3f_multiply(movement_axis, distance));
}

void	sphere_set_position(t_object *sphere, const t_vector3f position)
{
	sphere->position = position;
}

void	sphere_set_radius(t_object *sphere, const float radius)
{
	sphere->radius = radius;
	sphere_calculate_cache(sphere);
}
