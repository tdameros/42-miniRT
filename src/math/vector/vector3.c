/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:55:26 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/03 17:55:27 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "math/quaternion.h"

t_vector3f	vector3f_create(float x, float y, float z)
{
	t_vector3f	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

void	vector3f_print(t_vector3f vector)
{
	printf("Vector3 => x:%f y:%f, z:%f\n", vector.x, vector.y, vector.z);
}

float	vector3f_get(t_vector3f vector, t_axis axis)
{
	if (axis == X_AXIS)
		return (vector.x);
	else if (axis == Y_AXIS)
		return (vector.y);
	return (vector.z);
}

t_vector3f	get_normal_from_rotation(const t_vector3f rotation_degrees)
{
	t_vector3f	result;

	result = quaternionf_rotate_vector3f(rotation_degrees.x,
			(t_vector3f){1, 0, 0}, (t_vector3f){0, 1, 0});
	result = quaternionf_rotate_vector3f(rotation_degrees.y,
			(t_vector3f){0, 1, 0}, vector3f_unit(result));
	result = quaternionf_rotate_vector3f(rotation_degrees.z,
			(t_vector3f){0, 0, 1}, vector3f_unit(result));
	return (vector3f_unit(result));
}
