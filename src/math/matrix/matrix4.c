/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/03 18:01:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "math/matrix.h"

t_matrix4	matrix4_create(float value)
{
	t_matrix4	result;
	int			y;
	int			x;

	y = 0;
	x = 0;
	while (y < 4)
	{
		while (x < 4)
		{
			result.matrix[y][x] = value;
			x++;
		}
		x = 0;
		y++;
	}
	return (result);
}

t_matrix4	matrix4_create_identity(void)
{
	t_matrix4	result;

	result = matrix4_create(0);
	result.matrix[0][0] = 1;
	result.matrix[1][1] = 1;
	result.matrix[2][2] = 1;
	result.matrix[3][3] = 1;
	return (result);
}

/*						Translation matrix
[	1					0					0					0	]
[	0					1					0					0	]
[	0					0					1					0	]
[	x					y					z					1	]
*/
t_matrix4	create_translation_matrix(const t_vector3f translation)
{
	t_matrix4	result;

	result = matrix4_create_identity();
	result.matrix[3][0] = translation.x;
	result.matrix[3][1] = translation.y;
	result.matrix[3][2] = translation.z;
	return (result);
}

/*						Scale matrix
[	scale_factor		0					0					0	]
[	0					scale_factor		0					0	]
[	0					0					scale_factor		0	]
[	0					0					0					1	]
*/
t_matrix4	create_scale_matrix(const t_vector3f scale)
{
	t_matrix4	result;

	result = matrix4_create_identity();
	result.matrix[0][0] = scale.x;
	result.matrix[1][1] = scale.y;
	result.matrix[2][2] = scale.z;
	return (result);
}

void	matrix4_print(t_matrix4 matrix)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < 4)
	{
		while (x < 4)
		{
			printf("%f ", matrix.matrix[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}
