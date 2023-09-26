/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_rotation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:32:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/30 22:32:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/quaternion.h"
#include "math/conversion.h"

t_vector3f	quaternionf_rotate_vector3f(float angle, t_vector3f axis,
										t_vector3f vector)
{
	const float			radian_angle = convert_degrees_to_radians(angle);
	const t_quaternionf	vector_quaternion = quaternionf_create(0, vector);
	const t_quaternionf	quaternion_rotation = \
		quaternionf_angle_axis(radian_angle, axis);
	const t_quaternionf	quaternion_rotation_conjugate = \
			quaternionf_conjugate(quaternion_rotation);
	const t_quaternionf	rotated_quaternion = \
		quaternionf_multiply(quaternionf_multiply(quaternion_rotation, \
		vector_quaternion), quaternion_rotation_conjugate);

	return (rotated_quaternion.vector);
}
