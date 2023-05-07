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
	camera->direction = vector3_rotate_x(camera->direction, degrees);
}