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

#include "camera.h"
#include "conversion.h"

static t_matrix4	camera_perspective_fov(double fov,
						t_vector2 viewport,
						double near_clip,
						double far_clip);

void	camera_recalculate_projection(t_camera *camera)
{
	camera->projection = camera_perspective_fov(
			convert_degrees_to_radians(camera->vertical_fov),
			camera->viewport,
			camera->near_clip,
			camera->far_clip);
	camera->inverse_projection = matrix4_inverse(camera->projection);
}

static t_matrix4	camera_perspective_fov(double fov, t_vector2 viewport,
										double near_clip, double far_clip)
{
	t_matrix4		result;
	const double	rad = fov;
	const double	h = cos(0.5 * rad) / sin(0.5 * rad);
	const double	w = h * viewport.y / viewport.x;

	result = matrix4_create(0);
	result.matrix[0][0] = w;
	result.matrix[1][1] = h;
	result.matrix[2][2] = -((far_clip + near_clip) / (far_clip - near_clip));
	result.matrix[2][3] = -1;
	result.matrix[3][2] = -((2 * far_clip * near_clip)
			/ (far_clip - near_clip));
	return (result);
}
