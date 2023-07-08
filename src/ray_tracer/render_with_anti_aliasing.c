/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_with_anti_aliasing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:05:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/08 02:05:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "engine.h"
#include "ray_tracer/render.h"

#define PIXEL_DIVISION 2.f

typedef struct s_raytracing_anti_aliasing_routine_args
{
	// TODO move this in a header
	t_engine		*engine;
	int				*current_line;
	pthread_mutex_t	*current_line_mutex;
}	t_raytracing_anti_aliasing_routine_args;

static void			*render_raytracing_routine(void *args_void);
static unsigned int	get_color(const t_engine *engine, int x, int y);
static t_ray		get_ray(const t_engine *engine, float x, float y);

void	render_anti_aliased_raytracing(t_engine *minirt)
{
	pthread_t								threads[NB_OF_THREADS];
	t_raytracing_anti_aliasing_routine_args	thread_args[NB_OF_THREADS];
	pthread_mutex_t							mutex;
	int										current_screen_zone;

	// TODO secure thread functions
	pthread_mutex_init(&mutex, NULL);
	current_screen_zone = 0;
	for (size_t i = 0; i < NB_OF_THREADS - 1; i++)
		thread_args[i] = (t_raytracing_anti_aliasing_routine_args){minirt,
			&current_screen_zone, &mutex};
	for (size_t i = 0; i < NB_OF_THREADS - 1; i++)
		pthread_create(threads + i, NULL, &render_raytracing_routine, thread_args + i);
	for (size_t i = 0; i < NB_OF_THREADS; i++)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&mutex);
}

static void	*render_raytracing_routine(void *args_void)
{
	t_raytracing_anti_aliasing_routine_args	*args;
	int										x;
	int										y;
	unsigned int							*line;

	args = args_void;
	pthread_mutex_lock(args->current_line_mutex);
	while (*args->current_line < args->engine->ray_traced_image.height)
	{
		y = *args->current_line;
		(*args->current_line)++;
		pthread_mutex_unlock(args->current_line_mutex);

		line = args->engine->ray_traced_image.address
			+ y * args->engine->ray_traced_image.width;
		x = args->engine->ray_traced_image.width;
		while (x--)
			line[x] = get_color(args->engine, x, y);
		pthread_mutex_lock(args->current_line_mutex);
	}
	pthread_mutex_unlock(args->current_line_mutex);
	return (NULL);
}

static unsigned int	get_color(const t_engine *engine, const int x, const int y)
{
	int		sub_y;
	int		sub_x;
	t_color	color;
	t_ray	ray;

	ft_bzero(&color, sizeof(color));
	sub_y = PIXEL_DIVISION;
	while (sub_y--)
	{
		sub_x = PIXEL_DIVISION;
		while (sub_x--)
		{
			ray = get_ray(engine,
					x + sub_x / PIXEL_DIVISION + 1.f / PIXEL_DIVISION / 2.f,
					engine->ray_traced_image.height - 1.f
						- y + sub_y / PIXEL_DIVISION + 1.f / PIXEL_DIVISION / 2.f);
			color = vector3f_add(color, render_ray(ray, &engine->scene));
		}
	}
	color = vector3f_divide(color, PIXEL_DIVISION * PIXEL_DIVISION);
	color = vector3f_clamp(color, 0, 1);
	color = vector3f_multiply(color, 255);
	return (rgb_to_uint(color));
}

static t_ray	get_ray(const t_engine *engine, const float x, const float y)
{
	return (ray_create(engine->camera.position,
			get_ray_direction(&engine->camera, x, y)));
}
