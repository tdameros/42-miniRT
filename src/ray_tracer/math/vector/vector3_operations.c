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

#include "vector.h"

double	vector3_length_squared(t_vector3 vector)
{
	return (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

double	vector3_length(t_vector3 vector)
{
	return (sqrt(vector3_length_squared(vector)));
}

t_vector3	vector3_unit(t_vector3 vector)
{
	return (vector3_divide(vector, vector3_length(vector)));
}

double	vector3_dot(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3	vector3_cross(t_vector3 v1, t_vector3 v2)
{
	t_vector3	result;

	result = vector3_create(0, 0, 0);
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
