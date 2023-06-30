/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:27:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/30 22:27:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math/quaternion.h"

float	quaternionf_length(t_quaternionf quaternion)
{
	return (sqrtf(quaternion.scalar * quaternion.scalar
			+ vector3f_length_squared(quaternion.vector)));
}

t_quaternionf	quaternionf_unit(t_quaternionf quaternion)
{
	t_quaternionf	unit_quaternion;
	float			length;

	length = quaternionf_length(quaternion);
	unit_quaternion.vector = vector3f_divide(quaternion.vector, length);
	unit_quaternion.scalar = quaternion.scalar / length;
	return (unit_quaternion);
}

t_quaternionf	quaternionf_angle_axis(float angle, t_vector3f axis)
{
	const float		sin_angle = sinf(angle / 2);
	const float		cos_angle = cosf(angle / 2);
	t_quaternionf	quaternion;

	quaternion.vector = vector3f_multiply(axis, sin_angle);
	quaternion.scalar = cos_angle;
	return (quaternionf_unit(quaternion));
}

t_quaternionf	quaternionf_conjugate(t_quaternionf quaternion)
{
	t_quaternionf	conjugate_quaternion;

	conjugate_quaternion.scalar = quaternion.scalar;
	conjugate_quaternion.vector = vector3f_multiply(quaternion.vector, -1);
	return (conjugate_quaternion);
}
