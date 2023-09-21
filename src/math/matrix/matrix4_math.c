/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:25:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/21 16:56:15 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "math/matrix.h"

t_matrix4	matrix4_multiply(const t_matrix4 *m1, const t_matrix4 *m2)
{
	t_matrix4	result;
	int8_t		y;
	int8_t		x;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
			result.matrix[x][y] = m1->matrix[x][0] * m2->matrix[0][y]
				+ m1->matrix[x][1] * m2->matrix[1][y]
				+ m1->matrix[x][2] * m2->matrix[2][y]
				+ m1->matrix[x][3] * m2->matrix[3][y];
	}
	return (result);
}

t_vector4f	matrix4_multiply_vector4(const t_matrix4 *matrix, t_vector4f vector)
{
	t_vector4f	result;

	result.x = matrix->matrix[0][0] * vector.x
		+ matrix->matrix[1][0] * vector.y
		+ matrix->matrix[2][0] * vector.z
		+ matrix->matrix[3][0] * vector.w;
	result.y = matrix->matrix[0][1] * vector.x
		+ matrix->matrix[1][1] * vector.y
		+ matrix->matrix[2][1] * vector.z
		+ matrix->matrix[3][1] * vector.w;
	result.z = matrix->matrix[0][2] * vector.x
		+ matrix->matrix[1][2] * vector.y
		+ matrix->matrix[2][2] * vector.z
		+ matrix->matrix[3][2] * vector.w;
	result.w = matrix->matrix[0][3] * vector.x
		+ matrix->matrix[1][3] * vector.y
		+ matrix->matrix[2][3] * vector.z
		+ matrix->matrix[3][3] * vector.w;
	return (result);
}

//	vector w value is 1
t_vector3f	matrix4_multiply_vector3(const t_matrix4 *matrix,
				t_vector3f vector)
{
	t_vector3f	result;

	result.x = matrix->matrix[0][0] * vector.x
		+ matrix->matrix[1][0] * vector.y
		+ matrix->matrix[2][0] * vector.z
		+ matrix->matrix[3][0];
	result.y = matrix->matrix[0][1] * vector.x
		+ matrix->matrix[1][1] * vector.y
		+ matrix->matrix[2][1] * vector.z
		+ matrix->matrix[3][1];
	result.z = matrix->matrix[0][2] * vector.x
		+ matrix->matrix[1][2] * vector.y
		+ matrix->matrix[2][2] * vector.z
		+ matrix->matrix[3][2];
	return (result);
}
