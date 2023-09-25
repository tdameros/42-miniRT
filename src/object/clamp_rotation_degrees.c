/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp_rotation_degrees.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:29:06 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:29:06 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/vector.h"

t_vector3f	clamp_rotation_degrees(t_vector3f rotation_degrees)
{
	rotation_degrees.x = (int)rotation_degrees.x - (int)rotation_degrees.x % 10;
	rotation_degrees.y = (int)rotation_degrees.y - (int)rotation_degrees.y % 10;
	rotation_degrees.z = (int)rotation_degrees.z - (int)rotation_degrees.z % 10;
	if (rotation_degrees.x >= 360.f)
		rotation_degrees.x = (int)rotation_degrees.x % 360;
	if (rotation_degrees.y >= 360.f)
		rotation_degrees.y = (int)rotation_degrees.y % 360;
	if (rotation_degrees.z >= 360.f)
		rotation_degrees.z = (int)rotation_degrees.z % 360;
	while (rotation_degrees.x < 0.f)
		rotation_degrees.x += 360.f;
	while (rotation_degrees.y < 0.f)
		rotation_degrees.y += 360.f;
	while (rotation_degrees.z < 0.f)
		rotation_degrees.z += 360.f;
	return (rotation_degrees);
}
