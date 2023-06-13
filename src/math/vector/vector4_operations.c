/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:59:59 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/03 17:59:59 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math/vector.h"

float	vector4f_length_squared(t_vector4f vector)
{
	return (vector.x * vector.x
		+ vector.y * vector.y
		+ vector.z * vector.z
		+ vector.w * vector.w);
}

float	vector4f_length(t_vector4f vector)
{
	return (sqrtf(vector4f_length_squared(vector)));
}

t_vector4f	vector4f_unit(t_vector4f vector)
{
	return (vector4f_divide(vector, vector4f_length(vector)));
}

float	vector4f_dot(t_vector4f v1, t_vector4f v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}
