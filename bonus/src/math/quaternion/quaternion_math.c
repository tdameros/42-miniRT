/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_math.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:30:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/30 22:30:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/quaternion.h"

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
