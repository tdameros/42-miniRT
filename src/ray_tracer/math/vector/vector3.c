/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:55:26 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/03 17:55:27 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "vector.h"

t_vector3	vector3_create(double x, double y, double z)
{
	t_vector3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

void	vector3_print(t_vector3 vector)
{
	printf("Vector3 => x:%f y:%f, z:%f\n", vector.x, vector.y, vector.z);
}

t_vector3	vector3_clamp(t_vector3 vector, double min, double max)
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
