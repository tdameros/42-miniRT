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

#include "ray_tracer/camera.h"

void	camera_move_forward(t_camera *camera, float distance)
{
	camera->position = vector3f_add(camera->position, vector3f_multiply(
			vector3f_unit(camera->direction), distance));
}

void	camera_move_left(t_camera *camera, float distance)
{
	t_vector3f	right_direction;

	right_direction = vector3f_rotate_y(camera->direction, 90);
	camera->position = vector3f_add(camera->position, vector3f_multiply(
			vector3f_unit(right_direction), distance));
}

void	camera_rotate_left(t_camera *camera, float degrees)
{
	camera->direction = vector3f_rotate_y(camera->direction, degrees);
}

void	camera_rotate_up(t_camera *camera, float degrees)
{
	const float	up = degrees * (1.0 / 90.0);

	if (camera->direction.y + up < 1.0 && camera->direction.y + up > -1.0)
		camera->direction.y += up;
//	t_vector3f up_vector = vector3f_create(0, 1, 0);
//	t_vector3f right_vector = vector3f_cross(up_vector, vector3f_unit(camera->direction));
//	right_vector = vector3f_unit(right_vector);
//	t_matrix3 rotation_matrix = matrix3_rodrigues_rotation(right_vector, degrees);
//	camera->direction = matrix3_dot_vector3(rotation_matrix, camera->direction);
}