/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:56:33 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/03 17:56:33 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math/vector.h"

float	vector3f_length_squared(t_vector3f vector)
{
	return (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

float	vector3f_length(t_vector3f vector)
{
	return (sqrtf(vector3f_length_squared(vector)));
}

t_vector3f	vector3f_unit(t_vector3f vector)
{
	return (vector3f_divide(vector, vector3f_length(vector)));
}

float	vector3f_dot(t_vector3f v1, t_vector3f v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3f	vector3f_cross(t_vector3f v1, t_vector3f v2)
{
	t_vector3f	result;

	result = vector3f_create(0, 0, 0);
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
