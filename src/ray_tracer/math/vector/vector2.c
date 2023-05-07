/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:53:10 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/03 17:53:11 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "vector.h"

t_vector2	vector2_create(double x, double y)
{
	t_vector2	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

void	vector2_print(t_vector2 vector)
{
	printf("Vector2 => x:%f y:%f\n", vector.x, vector.y);
}

t_vector2	vector2_clamp(t_vector2 vector, double min, double max)
{
	if (vector.x < min)
		vector.x = min;
	if (vector.y < min)
		vector.y = min;
	if (vector.x > max)
		vector.x = max;
	if (vector.y > max)
		vector.y = max;
	return (vector);
}
