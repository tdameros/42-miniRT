/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:12:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/09 15:12:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/matrix.h"

t_vector3f	matrix3_dot_vector3(t_matrix3 matrix, t_vector3f vector)
{
	t_vector3f	result;

	result = vector3f_create(0, 0, 0);
	result.x = matrix.matrix[0][0] * vector.x
		+ matrix.matrix[0][1] * vector.y
		+ matrix.matrix[0][2] * vector.z;
	result.y = matrix.matrix[1][0] * vector.x
		+ matrix.matrix[1][1] * vector.y
		+ matrix.matrix[1][2] * vector.z;
	result.z = matrix.matrix[2][0] * vector.x
		+ matrix.matrix[2][1] * vector.y
		+ matrix.matrix[2][2] * vector.z;
	return (result);
}
