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
#include "math/quaternion.h"

void	camera_move_forward(t_camera *camera, float distance)
{
	camera->position = vector3f_add(camera->position, vector3f_multiply(
				vector3f_unit(camera->direction), distance));
}

void	camera_move_left(t_camera *camera, float distance)
{
	const t_vector3f	up_vector = vector3f_create(0, 1, 0);
	const t_vector3f	right_direction = vector3f_cross(up_vector,
			vector3f_unit(camera->direction));

	camera->position = vector3f_add(camera->position, vector3f_multiply(
				vector3f_unit(right_direction), distance));
}

void	camera_rotate_left(t_camera *camera, float degrees)
{
	const t_vector3f	rotate_axis = vector3f_create(0, 1, 0);

	camera->direction = quaternionf_rotate_vector3f(degrees, rotate_axis,
			camera->direction);
}

void	camera_rotate_up(t_camera *camera, float degrees)
{
	const t_vector3f	up_vector = vector3f_create(0, 1, 0);
	const t_vector3f	right_vector = vector3f_multiply(\
				vector3f_unit(vector3f_cross(up_vector, \
				vector3f_unit(camera->direction))), -1);

	if (camera->pitch + degrees < 89.0f
		&& camera->pitch + degrees > -89.0f)
	{
		camera->direction = quaternionf_rotate_vector3f(degrees, right_vector,
				camera->direction);
		camera->pitch += degrees;
	}
}
