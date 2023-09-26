/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:09:40 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/13 23:09:42 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libft.h"

#include "math/matrix.h"

static t_matrix4	create_rotation_x_matrix(const float theta);
static t_matrix4	create_rotation_y_matrix(const float theta);
static t_matrix4	create_rotation_z_matrix(const float theta);

t_matrix4	create_rotation_matrix(const t_vector3f degrees)
{
	const t_matrix4	x_rotation = create_rotation_x_matrix(
			ft_angle_to_theta(degrees.x));
	const t_matrix4	y_rotation = create_rotation_y_matrix(
			ft_angle_to_theta(degrees.y));
	const t_matrix4	z_rotation = create_rotation_z_matrix(
			ft_angle_to_theta(degrees.z));
	const t_matrix4	x_times_y = matrix4_multiply(&x_rotation, &y_rotation);

	return (matrix4_multiply(&x_times_y, &z_rotation));
}

/*						Rotation X matrix visualisation
[	1					0					0					0	]
[	0					cos(theta)			sin(theta)			0	]
[	0					-sin(theta)			cos(theta)			0	]
[	0					0					0					1	]
*/
static t_matrix4	create_rotation_x_matrix(const float theta)
{
	t_matrix4	result;

	result = matrix4_create_identity();
	result.matrix[1][1] = cos(theta);
	result.matrix[1][2] = sin(theta);
	result.matrix[2][1] = -sin(theta);
	result.matrix[2][2] = cos(theta);
	return (result);
}

/*						Rotation Y matrix
[	cos(theta)			0					sin(theta)			0	]
[	0					1					0					0	]
[	-sin(theta)			0					cos(theta)			0	]
[	0					0					0					1	]
*/
static t_matrix4	create_rotation_y_matrix(const float theta)
{
	t_matrix4	result;

	result = matrix4_create_identity();
	result.matrix[0][0] = cos(theta);
	result.matrix[0][2] = sin(theta);
	result.matrix[2][0] = -sin(theta);
	result.matrix[2][2] = cos(theta);
	return (result);
}

/*						Rotation Z matrix
[	cos(theta)			sin(theta)			0					0	]
[	-sin(theta)			cos(theta)			0					0	]
[	0					0					1					0	]
[	0					0					0					1	]
*/
static t_matrix4	create_rotation_z_matrix(const float theta)
{
	t_matrix4	result;

	result = matrix4_create_identity();
	result.matrix[0][0] = cos(theta);
	result.matrix[0][1] = sin(theta);
	result.matrix[1][0] = -sin(theta);
	result.matrix[1][1] = cos(theta);
	return (result);
}
