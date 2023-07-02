/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_round.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:31:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/02 01:31:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math/matrix.h"

t_matrix4	matrix4_round_diagonal(t_matrix4 matrix)
{
	matrix.matrix[0][0] = roundf(matrix.matrix[0][0] * 100000.0) / 100000.0;
	matrix.matrix[1][1] = roundf(matrix.matrix[1][1] * 100000.0) / 100000.0;
	matrix.matrix[2][2] = roundf(matrix.matrix[2][2] * 100000.0) / 100000.0;
	matrix.matrix[3][3] = roundf(matrix.matrix[3][3] * 100000.0) / 100000.0;
	return (matrix);
}
