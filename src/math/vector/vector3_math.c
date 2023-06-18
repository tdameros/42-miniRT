/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:56:05 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/03 17:56:06 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/vector.h"

t_vector3f	vector3f_add(t_vector3f v1, t_vector3f v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vector3f	vector3f_subtract(t_vector3f v1, t_vector3f v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vector3f	vector3f_multiply(t_vector3f v1, float value)
{
	v1.x *= value;
	v1.y *= value;
	v1.z *= value;
	return (v1);
}

t_vector3f	vector3f_divide(t_vector3f v1, float value)
{
	v1.x /= value;
	v1.y /= value;
	v1.z /= value;
	return (v1);
}

t_vector3f	vector3f_mult_vector3f(t_vector3f v1, t_vector3f v2)
{
	v1.x = v1.x * v2.x;
	v1.y = v1.y * v2.y;
	v1.z = v1.z * v2.z;
	return (v1);
}

