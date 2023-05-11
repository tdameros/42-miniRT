/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:18:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/04 16:18:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/camera.h"

static t_vector3f	get_ray_direction(t_camera *camera, int x, int y);

void	camera_recalculate_rays(t_camera *camera)
{
	int		y;
	int		x;
	t_ray	ray;

	y = 0;
	x = 0;
	while (y < (int) camera->viewport.y)
	{
		while (x < (int) camera->viewport.x)
		{
			ray = ray_create(camera->position, get_ray_direction(camera, x, y));
			camera->rays[x + y * (int) camera->viewport.x] = ray;
			x++;
		}
		x = 0;
		y++;
	}
}

static t_vector3f	get_ray_direction(t_camera *camera, int x, int y)
{
	t_vector2f	coord;
	t_vector4f	target;
	t_vector3f	perspective;
	t_vector4f	ray_direction;

	coord = vector2f_create(x / camera->viewport.x, y / camera->viewport.y);
	coord = vector2f_subtract(vector2f_multiply(coord, 2), vector2f_create(1, 1));
	target = matrix4_multiply_vector4(camera->inverse_projection,
									  vector4f_create(coord.x, coord.y, 1, 1));
	perspective = vector3f_unit(vector3f_divide(
			vector3f_create(target.x, target.y, target.z), target.w));
	ray_direction = vector4f_create(perspective.x,
									perspective.y,
									perspective.z,
									0);
	ray_direction = matrix4_multiply_vector4(camera->inverse_view,
			ray_direction);
	return (vector3f_create(ray_direction.x, ray_direction.y, ray_direction.z));
}
