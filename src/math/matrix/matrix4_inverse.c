/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_inverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:28:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/03 18:28:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/matrix.h"

static float	get_factor_to_one(float number);
static void		set_column_to_zero(t_matrix4 *matrix,
					t_matrix4 *identity_matrix, int x);
static void		multiply_row(t_matrix4 *matrix, int row, float factor);
static void		sum_column(t_matrix4 *matrix, int x, int y, float factor);

t_matrix4	matrix4_inverse(t_matrix4 matrix)
{
	t_matrix4	identity_matrix;
	int			x;
	float		factor;

	identity_matrix = matrix4_create_identity();
	x = 0;
	while (x < matrix.size)
	{
		factor = get_factor_to_one(matrix.matrix[x][x]);
		multiply_row(&identity_matrix, x, factor);
		multiply_row(&matrix, x, factor);
		set_column_to_zero(&matrix, &identity_matrix, x);
		x++;
	}
	return (identity_matrix);
}

static float	get_factor_to_one(float number)
{
	if (number == 0)
		return (0);
	return (1 / number);
}

static void	set_column_to_zero(t_matrix4 *matrix, t_matrix4 *identity_matrix,
								int x)
{
	int	y;

	y = 0;
	while (y < matrix->size)
	{
		if (x != y)
		{
			sum_column(identity_matrix, x, y, matrix->matrix[y][x]);
			sum_column(matrix, x, y, matrix->matrix[y][x]);
		}
		y++;
	}
}

static void	multiply_row(t_matrix4 *matrix, int row, float factor)
{
	int	i;

	i = 0;
	while (i < matrix->size)
	{
		matrix->matrix[row][i] *= factor;
		i++;
	}
}

static void	sum_column(t_matrix4 *matrix, int x, int y, float factor)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		matrix->matrix[y][i] -= factor * matrix->matrix[x][i];
		i++;
	}
}
