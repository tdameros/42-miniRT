/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:33:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:33:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/camera.h"
#include "math/quaternion.h"

void	camera_rotate_left(t_camera *camera, float degrees)
{
	const t_vector3f	rotate_axis = camera->up_vector;

	camera->direction = quaternionf_rotate_vector3f(degrees, rotate_axis,
			camera->direction);
}

void	camera_rotate_up(t_camera *camera, float degrees)
{
	const t_vector3f	up_vector = camera->up_vector;
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

void	camera_peek(t_camera *camera, float degrees)
{
	camera->up_vector = quaternionf_rotate_vector3f(degrees,
			camera->direction, camera->up_vector);
}

void	camera_set_horizontal_fov(t_camera *camera, float horizontal_fov)
{
	if (horizontal_fov <= 0)
		camera->horizontal_fov = 1;
	else if (horizontal_fov >= 180)
		camera->horizontal_fov = 179;
	else
		camera->horizontal_fov = horizontal_fov;
}
