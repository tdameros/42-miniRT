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
#include "threads.h"

static void	*recalculate_rays_routine(void *arg_void);
static void	recalculate_rays_on_failure(void *arg_void);

void	camera_recalculate_rays(t_camera *camera)
{
	t_recalculate_rays_args	arg;

	arg.camera = camera;
	arg.current_line = 0;
	start_threads(&arg, &recalculate_rays_routine, recalculate_rays_on_failure);
}

static void	*recalculate_rays_routine(void *arg_void)
{
	t_recalculate_rays_args			*data;
	pthread_mutex_t					*mutex;
	t_ray							*line;
	int								y;
	int								x;

	data = ((t_routine_arg *)arg_void)->arg;
	mutex = &((t_routine_arg *)arg_void)->mutex;
	pthread_mutex_lock(mutex);
	while (data->current_line < data->camera->viewport.size.y)
	{
		y = data->current_line;
		data->current_line++;
		pthread_mutex_unlock(mutex);
		line = data->camera->rays
			+ (int)((data->camera->viewport.size.y - y - 1)
				* data->camera->viewport.size.x);
		x = data->camera->viewport.size.x;
		while (x--)
			line[x] = ray_create(data->camera->position,
					get_ray_direction(data->camera, x, y));
		pthread_mutex_lock(mutex);
	}
	pthread_mutex_unlock(mutex);
	return (NULL);
}

static void	recalculate_rays_on_failure(void *arg_void)
{
	t_recalculate_rays_args			*data;
	t_ray							*line;
	int								y;
	int								x;

	data = arg_void;
	while (data->current_line < data->camera->viewport.size.y)
	{
		y = data->current_line;
		data->current_line++;
		line = data->camera->rays
			+ (int)((data->camera->viewport.size.y - y - 1)
				* data->camera->viewport.size.x);
		x = data->camera->viewport.size.x;
		while (x--)
			line[x] = ray_create(data->camera->position,
					get_ray_direction(data->camera, x, y));
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
