/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quatf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:43:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/28 18:43:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math/quaternion.h"

t_quaternionf	quaternionf_create(float scalar, t_vector3f vector)
{
	t_quaternionf	quaternion;

	quaternion.scalar = scalar;
	quaternion.vector = vector;
	return (quaternion);
}

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

t_quaternionf	quaternionf_axis_angle(t_vector3f axis, float angle)
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

t_quaternionf	quaternionf_multiply(t_quaternionf q1, t_quaternionf q2)
{
	t_quaternionf	result;

	result.scalar = q1.scalar * q2.scalar
		- q1.vector.x * q2.vector.x
		- q1.vector.y * q2.vector.y
		- q1.vector.z * q2.vector.z;
	result.vector.x = q1.scalar * q2.vector.x
		+ q1.vector.x * q2.scalar
		+ q1.vector.y * q2.vector.z
		- q1.vector.z * q2.vector.y;
	result.vector.y = q1.scalar * q2.vector.y
		- q1.vector.x * q2.vector.z
		+ q1.vector.y * q2.scalar
		+ q1.vector.z * q2.vector.x;
	result.vector.z = q1.scalar * q2.vector.z
		+ q1.vector.x * q2.vector.y
		- q1.vector.y * q2.vector.x
		+ q1.vector.z * q2.scalar;
	return (result);
}

t_vector3f	quaternionf_rotate_vector3f(float angle, t_vector3f axis,
										t_vector3f vector)
{
	vector = vector3f_unit(vector);
	const t_quaternionf	vector_quaternion = quaternionf_create(0, vector);
	const t_quaternionf	quaternion_rotation = \
			quaternionf_axis_angle(axis, angle);
	const t_quaternionf	quaternion_rotation_conjugate = \
			quaternionf_conjugate(quaternion_rotation);
	const t_quaternionf	rotated_quaternion = \
			quaternionf_multiply(quaternionf_multiply(quaternion_rotation, \
			vector_quaternion), quaternion_rotation_conjugate);

	return (rotated_quaternion.vector);
}
