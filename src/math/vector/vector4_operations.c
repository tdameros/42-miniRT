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

double	vector4_length_squared(t_vector4 vector)
{
	return (vector.x * vector.x
		+ vector.y * vector.y
		+ vector.z * vector.z
		+ vector.w * vector.w);
}

double	vector4_length(t_vector4 vector)
{
	return (sqrt(vector4_length_squared(vector)));
}

t_vector4	vector4_unit(t_vector4 vector)
{
	return (vector4_divide(vector, vector4_length(vector)));
}

double	vector4_dot(t_vector4 v1, t_vector4 v4)
{
	return (v1.x * v4.x + v1.y * v4.y + v1.z * v4.z + v1.w * v4.w);
}
