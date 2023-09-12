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

#include <pthread.h>

#include "engine.h"

typedef struct s_recalculate_rays_args
{
	// TODO move this in a header
	t_camera		*camera;
	int				*current_line;
	pthread_mutex_t	*current_line_mutex;
}	t_recalculate_rays_args;

static void			*recalculate_rays_routine(void *args_void);

void	camera_recalculate_rays(t_camera *camera)
{
	pthread_t				threads[NB_OF_THREADS];
	t_recalculate_rays_args	thread_args[NB_OF_THREADS];
	pthread_mutex_t			mutex;
	int						current_line;

	// TODO secure thread functions
	pthread_mutex_init(&mutex, NULL);
	current_line = 0;
	for (size_t i = 0; i < NB_OF_THREADS - 1; i++)
		thread_args[i] = (t_recalculate_rays_args){camera, &current_line, &mutex};
	for (size_t i = 0; i < NB_OF_THREADS - 1; i++)
		pthread_create(threads + i, NULL, &recalculate_rays_routine, thread_args + i);
	for (size_t i = 0; i < NB_OF_THREADS; i++)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&mutex);
}

static void	*recalculate_rays_routine(void *args_void)
{
	const t_recalculate_rays_args	*args = args_void;
	t_ray							*line;
	int								y;
	int								x;

	pthread_mutex_lock(args->current_line_mutex);
	while (*args->current_line < args->camera->viewport.size.y)
	{
		y = *args->current_line;
		(*args->current_line)++;
		pthread_mutex_unlock(args->current_line_mutex);

		line = args->camera->rays
			+ (int)((args->camera->viewport.size.y - y - 1)
				* args->camera->viewport.size.x);
		x = args->camera->viewport.size.x;
		while (x--)
			line[x] = ray_create(args->camera->position,
					get_ray_direction(args->camera, x, y));

		pthread_mutex_lock(args->current_line_mutex);
	}
	pthread_mutex_unlock(args->current_line_mutex);
	return (NULL);
}

t_vector3f	get_ray_direction(const t_camera *camera, const float x,
				const float y)
{
	t_vector2f	coord;
	t_vector4f	target;
	t_vector3f	perspective;
	t_vector4f	ray_direction;

	coord = vector2f_create(x / camera->viewport.size.x, y / camera->viewport.size.y);
	coord = vector2f_subtract(vector2f_multiply(coord, 2), vector2f_create(1, 1));
	target = matrix4_multiply_vector4(&camera->inverse_projection,
									  vector4f_create(coord.x, coord.y, 1, 1));
	perspective = vector3f_unit(vector3f_divide(
			vector3f_create(target.x, target.y, target.z), target.w));
	ray_direction = vector4f_create(perspective.x,
									perspective.y,
									perspective.z,
									0);
	ray_direction = matrix4_multiply_vector4(&camera->inverse_view,
			ray_direction);
	return (vector3f_create(ray_direction.x, ray_direction.y, ray_direction.z));
}
