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
#include <stdbool.h>

#include "math/vector.h"

t_vector2f	vector2f_create(float x, float y)
{
	t_vector2f	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

void	vector2f_print(t_vector2f vector)
{
	printf("Vector2 => x:%f y:%f\n", vector.x, vector.y);
}

t_vector2f	vector2f_clamp(t_vector2f vector, float min, float max)
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

bool	vector2f_are_equal(const t_vector2f v1, const t_vector2f v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}
