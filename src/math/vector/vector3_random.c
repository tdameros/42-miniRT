/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_random.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:41:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/14 19:41:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "math/vector.h"

float	float_rand(float min, float max)
{
	const float	scale = rand() / (float) RAND_MAX;

	return (min + scale * (max - min));
}

float float_rand_distribution(float min, float max)
{
	// Thanks to https://stackoverflow.com/a/6178290
	float theta = 2 * 3.1415926 * float_rand(min, max);
	float rho = sqrtf(-2 * logf(float_rand(min, max)));
	return rho * cosf(theta);
}

t_vector3f	vector3f_random(float min, float max)
{
	return (vector3f_create(float_rand_distribution(min, max),
							float_rand_distribution(min, max),
							float_rand_distribution(min, max)));
}



