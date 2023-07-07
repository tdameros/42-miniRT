/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:05:21 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/20 18:05:23 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/vector.h"
#include "ray_tracer/rays.h"
#include "scene.h"
#include "object.h"
#include "ray_tracer/shade.h"
#include "engine.h"

static t_color		render_pixel(t_engine *engine, size_t ray_index);
static t_vector3f	render_ray(t_ray ray, const t_scene *scene);

float random_value(unsigned int index)
{
	index *= 9694;
	index *= index;
	return ((float)index / 4294967295.0f);
}
#include <stdlib.h>
#include <stdio.h>
//static float	generate_randomf(float min, float max)
//{
//	return ((rand() % (int)(max - min + 1)) + min);
//}

#include <pthread.h>

typedef struct s_raytracing_routine_args
{
	t_engine		*engine;
	int				*current_line;
	pthread_mutex_t	*current_line_mutex;
	int				incrementer;
}	t_raytracing_routine_args;

static void	*render_raytracing_routine(void *args_void);

#define NB_OF_THREADS 16

///
/// \param minirt
/// \param incrementer > 0
void	render_raytracing(t_engine *minirt, const int incrementer)
{
	pthread_t					threads[NB_OF_THREADS];
	t_raytracing_routine_args	thread_args[NB_OF_THREADS];
	pthread_mutex_t				mutex;
	int							current_screen_zone;

	pthread_mutex_init(&mutex, NULL);
	current_screen_zone = 0;
	for (size_t i = 0; i < NB_OF_THREADS - 1; i++)
		thread_args[i] = (t_raytracing_routine_args){minirt, &current_screen_zone, &mutex, incrementer};
	for (size_t i = 0; i < NB_OF_THREADS - 1; i++)
		pthread_create(threads + i, NULL, &render_raytracing_routine, thread_args + i);
	for (size_t i = 0; i < NB_OF_THREADS; i++)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&mutex);
}

static void	*render_raytracing_routine(void *args_void)
{
	t_raytracing_routine_args	*args;
	size_t						i;
	size_t						limit;

	args = args_void;
	pthread_mutex_lock(args->current_line_mutex);
	while (*args->current_line < args->engine->ray_traced_image.height)
	{
		i = *args->current_line * args->engine->ray_traced_image.width;
		*args->current_line += args->incrementer;
		pthread_mutex_unlock(args->current_line_mutex);

		limit = i + args->engine->ray_traced_image.width;
		while (i < limit)
		{
			args->engine->raytraced_pixels.data[i] = render_pixel(args->engine, i);
			i += args->incrementer;
		}

		pthread_mutex_lock(args->current_line_mutex);
	}
	pthread_mutex_unlock(args->current_line_mutex);
	return (NULL);
}

static t_color	render_pixel(t_engine *engine, size_t ray_index)
{
	const t_ray	ray = engine->camera.rays[ray_index];
	t_vector3f	pixel_color;

	pixel_color = render_ray(ray, &engine->scene);
	pixel_color = vector3f_clamp(pixel_color, 0, 1);
	pixel_color = vector3f_multiply(pixel_color, 255);
	return (pixel_color);
}

static t_vector3f	render_ray(t_ray ray, const t_scene *scene)
{
	t_hit			ray_hit;
	t_vector3f		ray_color;
	t_vector3f		color;
	const int		bounces_per_pixel = 5;
	float			multiplier;

	multiplier = 1.0f;
	ray_color = vector3f_create(0, 0, 0);
	for (int i = 0; i < bounces_per_pixel; i++)
	{
		ray_hit = calculate_ray_intersection(&ray, scene);
		if (!ray_hit.hit)
		{
			color = vector3f_multiply(scene->sky_color, multiplier);
			ray_color = vector3f_add(ray_color, color);
			return (ray_color);
		}

		// Lights
//		color = calculate_color(scene, ray_hit, multiplier);
		color = calculate_shade(scene, ray_hit, multiplier);
		ray_color = vector3f_add(ray_color, color);
		multiplier *= ray_hit.object->material.reflect;
		ray.origin = vector3f_add(ray_hit.position, vector3f_multiply(ray_hit.normal, 0.0001f));
		ray.direction = reflect(ray.direction, ray_hit.normal);
	}
	return (ray_color);
}
