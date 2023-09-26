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

#include <math.h>

#include "math/vector.h"

t_vector3f	vector3f_clamp(t_vector3f vector, float min, float max)
{
	vector.x = fmaxf(vector.x, min);
	vector.y = fmaxf(vector.y, min);
	vector.z = fmaxf(vector.z, min);
	vector.x = fminf(vector.x, max);
	vector.y = fminf(vector.y, max);
	vector.z = fminf(vector.z, max);
	return (vector);
}

t_vector3f	vector3f_min(t_vector3f a, t_vector3f b)
{
	return ((t_vector3f){
		fminf(a.x, b.x),
		fminf(a.y, b.y),
		fminf(a.z, b.z)});
}

t_vector3f	vector3f_max(t_vector3f a, t_vector3f b)
{
	return ((t_vector3f){
		fmaxf(a.x, b.x),
		fmaxf(a.y, b.y),
		fmaxf(a.z, b.z)});
}
