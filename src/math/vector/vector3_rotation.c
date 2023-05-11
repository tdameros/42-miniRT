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

#include "math/vector.h"
#include "math/conversion.h"

t_vector3f	vector3f_rotate_x(t_vector3f vector, float degrees)
{
	const float	radians = convert_degrees_to_radians(degrees);
	const float	cos_result = cosf(radians);
	const float	sin_result = sinf(radians);
	t_vector3f		result;

	result = vector3f_create(0, 0, 0);
	result.x = vector.x;
	result.y = cos_result * vector.y - sin_result * vector.z;
	result.z = sin_result * vector.y + cos_result * vector.z;
	return (result);
}

t_vector3f	vector3f_rotate_y(t_vector3f vector, float degrees)
{
	const float	radians = convert_degrees_to_radians(degrees);
	const float	cos_result = cosf(radians);
	const float	sin_result = sinf(radians);
	t_vector3f		result;

	result = vector3f_create(0, 0, 0);
	result.x = cos_result * vector.x + sin_result * vector.z;
	result.y = vector.y;
	result.z = -sin_result * vector.x + cos_result * vector.z;
	return (result);
}

t_vector3f	vector3f_rotate_z(t_vector3f vector, float degrees)
{
	const float	radians = convert_degrees_to_radians(degrees);
	const float	cos_result = cosf(radians);
	const float	sin_result = sinf(radians);
	t_vector3f		result;

	result = vector3f_create(0, 0, 0);
	result.x = cos_result * vector.x - sin_result * vector.y;
	result.y = sin_result * vector.x + cos_result * vector.y;
	result.z = vector.z;
	return (result);
}
