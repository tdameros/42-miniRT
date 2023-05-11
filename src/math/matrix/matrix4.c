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

	result.size = 4;
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

void	matrix4_print(t_matrix4 matrix)
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
