/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:59:36 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/03 17:59:36 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/vector.h"

t_vector4	vector4_add(t_vector4 v1, t_vector4 v4)
{
	v1.x += v4.x;
	v1.y += v4.y;
	v1.z += v4.z;
	v1.w += v4.w;
	return (v1);
}

t_vector4	vector4_subtract(t_vector4 v1, t_vector4 v4)
{
	v1.x -= v4.x;
	v1.y -= v4.y;
	v1.z -= v4.z;
	v1.w -= v4.w;
	return (v1);
}

t_vector4	vector4_multiply(t_vector4 v1, float value)
{
	v1.x *= value;
	v1.y *= value;
	v1.z *= value;
	v1.w *= value;
	return (v1);
}

t_vector4	vector4_divide(t_vector4 v1, float value)
{
	v1.x /= value;
	v1.y /= value;
	v1.z /= value;
	v1.w /= value;
	return (v1);
}
