/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:11:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/09 15:11:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "math/matrix.h"

t_matrix3	matrix3_create(double value)
{
	t_matrix3	result;
	int			y;
	int			x;

	result.size = 3;
	y = 0;
	x = 0;
	while (y < result.size)
	{
		while (x < result.size)
		{
			result.matrix[y][x] = value;
			x++;
		}
		x = 0;
		y++;
	}
	return (result);
}

t_matrix3	matrix3_create_identity(void)
{
	t_matrix3	result;

	result = matrix3_create(0);
	result.matrix[0][0] = 1;
	result.matrix[1][1] = 1;
	result.matrix[2][2] = 1;
	return (result);
}

void	matrix3_print(t_matrix3 matrix)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < matrix.size)
	{
		while (x < matrix.size)
		{
			printf("%f ", matrix.matrix[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}
