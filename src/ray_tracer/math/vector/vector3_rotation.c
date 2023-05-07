/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_rotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:04:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/07 14:04:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vector.h"
#include "conversion.h"

t_vector3	vector3_rotate_x(t_vector3 vector, double degrees)
{
	const double	radians = convert_degrees_to_radians(degrees);
	const double	cos_result = cos(radians);
	const double	sin_result = sin(radians);
	t_vector3		result;

	result = vector3_create(0, 0, 0);
	result.x = vector.x;
	result.y = cos_result * vector.y - sin_result * vector.z;
	result.z = sin_result * vector.y + cos_result * vector.z;
	return (result);
}

t_vector3	vector3_rotate_y(t_vector3 vector, double degrees)
{
	const double	radians = convert_degrees_to_radians(degrees);
	const double	cos_result = cos(radians);
	const double	sin_result = sin(radians);
	t_vector3		result;

	result = vector3_create(0, 0, 0);
	result.x = cos_result * vector.x + sin_result * vector.z;
	result.y = vector.y;
	result.z = -sin_result * vector.x + cos_result * vector.z;
	return (result);
}

t_vector3	vector3_rotate_z(t_vector3 vector, double degrees)
{
	const double	radians = convert_degrees_to_radians(degrees);
	const double	cos_result = cos(radians);
	const double	sin_result = sin(radians);
	t_vector3		result;

	result = vector3_create(0, 0, 0);
	result.x = cos_result * vector.x - sin_result * vector.y;
	result.y = sin_result * vector.x + cos_result * vector.y;
	result.z = vector.z;
	return (result);
}
