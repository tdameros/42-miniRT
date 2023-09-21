/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_limit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:27:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/15 22:27:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/vector.h"

t_vector3f	vector3f_clamp(t_vector3f vector, float min, float max)
{
	if (vector.x < min)
		vector.x = min;
	if (vector.y < min)
		vector.y = min;
	if (vector.z < min)
		vector.z = min;
	if (vector.x > max)
		vector.x = max;
	if (vector.y > max)
		vector.y = max;
	if (vector.z > max)
		vector.z = max;
	return (vector);
}

t_vector3f	vector3f_min(t_vector3f a, t_vector3f b)
{
	if (b.x < a.x)
		a.x = b.x;
	if (b.y < a.y)
		a.y = b.y;
	if (b.z < a.z)
		a.z = b.z;
	return (a);
}

t_vector3f	vector3f_max(t_vector3f a, t_vector3f b)
{
	if (b.x > a.x)
		a.x = b.x;
	if (b.y > a.y)
		a.y = b.y;
	if (b.z > a.z)
		a.z = b.z;
	return (a);
}
