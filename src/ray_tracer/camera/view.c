/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:37:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/04 15:37:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/camera.h"

static t_matrix4	camera_look_at(t_vector3 eye,
						t_vector3 center,
						t_vector3 up);

void	camera_recalculate_view(t_camera *camera)
{
	camera->view = camera_look_at(camera->position,
			vector3_add(camera->position, camera->direction),
			vector3_create(0, 1, 0));
	camera->inverse_view = matrix4_inverse(camera->view);
}

static t_matrix4	camera_look_at(t_vector3 eye,
									t_vector3 center,
									t_vector3 up)
{
	t_vector3	f;
	t_vector3	s;
	t_vector3	u;
	t_matrix4	result;

	f = vector3_unit(vector3_subtract(center, eye));
	s = vector3_unit(vector3_cross(f, up));
	u = vector3_cross(s, f);
	result = matrix4_create(0);
	result.matrix[0][0] = s.x;
	result.matrix[1][0] = s.y;
	result.matrix[2][0] = s.z;
	result.matrix[0][1] = u.x;
	result.matrix[1][1] = u.y;
	result.matrix[2][1] = u.z;
	result.matrix[0][2] = -f.x;
	result.matrix[1][2] = -f.y;
	result.matrix[2][2] = -f.z;
	result.matrix[3][0] = -vector3_dot(s, eye);
	result.matrix[3][1] = -vector3_dot(u, eye);
	result.matrix[3][2] = vector3_dot(f, eye);
	return (result);
}
