/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:43:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/28 18:43:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# include "math/matrix.h"

typedef struct s_quaternionf
{
	float		scalar;
	t_vector3f	vector;
}	t_quaternionf;

//	quaternion.c
t_quaternionf	quaternionf_create(float scalar, t_vector3f vector);

//	quaternion_rotation.c
t_vector3f		quaternionf_rotate_vector3f(float angle, t_vector3f axis,
					t_vector3f vector);

//	quaternion_math.c
t_quaternionf	quaternionf_multiply(t_quaternionf q1, t_quaternionf q2);

//	quaternion_operations.c
float			quaternionf_length(t_quaternionf quaternion);
t_quaternionf	quaternionf_unit(t_quaternionf quaternion);
t_quaternionf	quaternionf_angle_axis(float angle, t_vector3f axis);
t_quaternionf	quaternionf_conjugate(t_quaternionf quaternion);

#endif