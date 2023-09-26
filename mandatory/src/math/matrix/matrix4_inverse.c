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

#include "float.h"

#include "libft.h"

#include "math/matrix.h"

static void		swap_pivot(t_matrix4 *matrix, t_matrix4 *identity,
					int current_row);
static void		multiply_row(t_matrix4 *matrix, int row, float factor);
static void		set_column_to_zero(t_matrix4 *matrix,
					t_matrix4 *identity_matrix, int x);
static void		sum_column(t_matrix4 *matrix, int x, int y, float factor);

t_matrix4	matrix4_inverse(t_matrix4 matrix)
{
	t_matrix4	identity_matrix;
	int			x;
	float		pivot;
	float		factor;

	identity_matrix = matrix4_create_identity();
	x = 0;
	while (x < 4)
	{
		pivot = matrix.matrix[x][x];
		if (ft_is_equalsf(pivot, 0, FLT_EPSILON))
		{
			matrix.matrix[x][x] = 0;
			swap_pivot(&matrix, &identity_matrix, x);
		}
		factor = 1 / matrix.matrix[x][x];
		multiply_row(&identity_matrix, x, factor);
		multiply_row(&matrix, x, factor);
		set_column_to_zero(&matrix, &identity_matrix, x);
		x++;
	}
	return (identity_matrix);
}

static void	swap_pivot(t_matrix4 *matrix, t_matrix4 *identity, int current_row)
{
	int		row;
	int		column;
	float	temp;

	row = current_row;
	while (matrix->matrix[row][current_row] == 0)
		row++;
	column = 0;
	while (column < 4)
	{
		temp = matrix->matrix[row][column];
		matrix->matrix[row][column] = matrix->matrix[current_row][column];
		matrix->matrix[current_row][column] = temp;
		column++;
	}
	column = 0;
	while (column < 4)
	{
		temp = identity->matrix[row][column];
		identity->matrix[row][column] = identity->matrix[current_row][column];
		identity->matrix[current_row][column] = temp;
		column++;
	}
}

static void	multiply_row(t_matrix4 *matrix, int row, float factor)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		matrix->matrix[row][i] *= factor;
		i++;
	}
}

static void	set_column_to_zero(t_matrix4 *matrix, t_matrix4 *identity_matrix,
								int x)
{
	int	y;

	y = 0;
	while (y < 4)
	{
		if (x != y)
		{
			sum_column(identity_matrix, x, y, matrix->matrix[y][x]);
			sum_column(matrix, x, y, matrix->matrix[y][x]);
		}
		y++;
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
