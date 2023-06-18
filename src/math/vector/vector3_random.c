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

float	next_random(unsigned int *seed)
{
	unsigned int	result;

	*seed = *seed * 747796405 + 2891336453;
	result = ((*seed >> ((*seed >> 28) + 4)) ^ *seed) * 277803737;
	result = (result >> 22) ^ result;
	return result;
}

float	float_rand(unsigned int *seed)
{
	return (next_random(seed)  / 4294967295.0);
}

float float_rand_distribution(unsigned int *seed)
{
	// Thanks to https://stackoverflow.com/a/6178290
	float theta = 2 * 3.1415926 * float_rand(seed);
	float rho = sqrtf(-2 * logf(float_rand(seed)));
	return rho * cosf(theta);
}

t_vector3f	vector3f_random(unsigned int *seed)
{
	return (vector3f_create(float_rand_distribution(seed),
							float_rand_distribution(seed),
							float_rand_distribution(seed)));
}



