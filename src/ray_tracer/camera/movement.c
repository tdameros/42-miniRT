/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:29:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/07 14:29:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	camera_move_forward(t_camera *camera, double distance)
{
	camera->position = vector3_add(camera->position, vector3_multiply(
				vector3_unit(camera->direction), distance));
}

void	camera_move_left(t_camera *camera, double distance)
{
	t_vector3	right_direction;

	right_direction = vector3_rotate_y(camera->direction, 90);
	camera->position = vector3_add(camera->position, vector3_multiply(
				vector3_unit(right_direction), distance));
}

void	camera_rotate_left(t_camera *camera, double degrees)
{
	camera->direction = vector3_rotate_y(camera->direction, degrees);
}

void	camera_rotate_up(t_camera *camera, double degrees)
{
	const double	up = degrees * (1.0 / 90.0);

	if (camera->direction.y + up < 1.0 && camera->direction.y + up > -1.0)
		camera->direction.y += up;
//	t_vector3 up_vector = vector3_create(0, 1, 0);
//	t_vector3 right_vector = vector3_cross(up_vector, vector3_unit(camera->direction));
//	right_vector = vector3_unit(right_vector);
//	t_matrix3 rotation_matrix = matrix3_rodrigues_rotation(right_vector, degrees);
//	camera->direction = matrix3_dot_vector3(rotation_matrix, camera->direction);
}