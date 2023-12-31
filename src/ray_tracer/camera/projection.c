/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:37:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/04 15:37:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ray_tracer/camera.h"
#include "math/conversion.h"

static t_matrix4	camera_perspective_fov(float horizontal_fov,
						t_vector2f viewport,
						float near_clip,
						float far_clip);

void	camera_recalculate_projection(t_camera *camera)
{
	camera->projection = camera_perspective_fov(
			convert_degrees_to_radians(camera->horizontal_fov),
			camera->viewport.size,
			camera->near_clip,
			camera->far_clip);
	camera->inverse_projection = matrix4_inverse(camera->projection);
}

static t_matrix4	camera_perspective_fov(float horizontal_fov,
											t_vector2f viewport,
											float near_clip, float far_clip)
{
	t_matrix4		result;
	const float		aspect_ratio = viewport.x / viewport.y;
	const float		fov_vertical = 2 * atanf(tanf(horizontal_fov / 2)
			/ aspect_ratio);

	result = matrix4_create(0);
	result.matrix[0][0] = 1.f / tanf(horizontal_fov / 2);
	result.matrix[1][1] = 1.f / tanf(fov_vertical / 2);
	result.matrix[2][2] = -((far_clip + near_clip) / (far_clip - near_clip));
	result.matrix[2][3] = -1;
	result.matrix[3][2] = -((2 * far_clip * near_clip)
			/ (far_clip - near_clip));
	return (result);
}
