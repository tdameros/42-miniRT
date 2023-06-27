/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:17:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/04 16:17:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ray_tracer/camera.h"

int	camera_create(t_camera *camera, t_vector2f viewport)
{
//	camera->position = vector3f_create(0, 0, 3);
//	camera->direction = vector3f_create(0, 0, -1);
	camera->position = vector3f_create(0, 5.161712f, 7.150213f);
	camera->direction = vector3f_create(1.000002f, -0.222222f, -0.000000f);
	camera->view = matrix4_create_identity();
	camera->inverse_view = matrix4_create_identity();
	camera->projection = matrix4_create_identity();
	camera->inverse_projection = matrix4_create_identity();
	camera->vertical_fov = 45;
	camera->near_clip = 0.1f;
	camera->far_clip = 100;
	camera->viewport.size = viewport;
	camera->viewport.number_of_pixels
		= camera->viewport.size.x * camera->viewport.size.y;
	camera->rays = malloc(sizeof(*camera->rays)
			* camera->viewport.number_of_pixels);
	if (camera->rays == NULL)
		return (-1);
	camera_recalculate_view(camera);
	camera_recalculate_projection(camera);
	camera_recalculate_rays(camera);
	return (0);
}
