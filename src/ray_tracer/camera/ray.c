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

#include "engine.h"

void	camera_recalculate_rays(t_camera *camera)
{
	int		x;
	int		y;
	t_ray	*cursor;

	y = 0;
	cursor = camera->rays;
	while (y < camera->viewport.size.y)
	{
		x = 0;
		while (x < camera->viewport.size.x)
		{
			*cursor = ray_create(camera->position,
					get_ray_direction(camera, x, y));
			cursor++;
			x++;
		}
		y++;
	}
}

t_vector3f	get_ray_direction(const t_camera *camera, const float x,
				const float y)
{
	t_vector2f	coord;
	t_vector4f	target;
	t_vector3f	perspective;
	t_vector4f	ray_direction;

	coord = vector2f_create(x / camera->viewport.size.x,
			y / camera->viewport.size.y);
	coord = vector2f_subtract(vector2f_multiply(coord, 2),
			vector2f_create(1, 1));
	target = matrix4_multiply_vector4(&camera->inverse_projection,
			vector4f_create(coord.x, coord.y, 1, 1));
	perspective = vector3f_unit(vector3f_divide(
				vector3f_create(target.x, target.y, target.z), target.w));
	ray_direction = vector4f_create(perspective.x,
			perspective.y, perspective.z, 0);
	ray_direction = matrix4_multiply_vector4(&camera->inverse_view,
			ray_direction);
	return (vector3f_create(ray_direction.x, ray_direction.y, ray_direction.z));
}
