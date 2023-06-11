/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_angle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:46:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/08 16:46:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math/vector.h"
#include "math/conversion.h"

float	vector3f_get_angle(t_vector3f a, t_vector3f b)
{
	float	cos;

	cos = vector3f_dot(a, b) / (vector3f_length(a) * vector3f_length(b));
	return (convert_radians_to_degrees(acosf(cos)));
}
