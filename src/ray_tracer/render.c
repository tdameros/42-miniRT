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
#include "ray_tracer/lights.h"
#include "engine.h"

static t_color		render_pixel(t_engine *engine, size_t ray_index);
static t_vector3f	render_ray(t_ray ray, const t_scene *scene);

#include <pthread.h>
typedef struct s_tmp
{
	t_engine	*engine;
	size_t		i;
	size_t		limit;
}	t_tmp;
static void	*render_raytracing_part(void *tmp_void);

#define NB_OF_THREADS 16

void	render_raytracing(t_engine *minirt)
{
	size_t	max = minirt->ray_traced_image.width * minirt->ray_traced_image.height;
	size_t max_divided_by_thread_count = max / NB_OF_THREADS;
	pthread_t	threads[NB_OF_THREADS];
	t_tmp		tmps[NB_OF_THREADS];

	for (size_t i = 0; i < NB_OF_THREADS - 1; i++)
	{
		tmps[i].engine = minirt;
		tmps[i].i = max_divided_by_thread_count * i;
		tmps[i].limit = max_divided_by_thread_count * (i + 1);
		pthread_create(threads + i, NULL, &render_raytracing_part, tmps + i);
	}
	tmps[NB_OF_THREADS - 1].engine = minirt;
	tmps[NB_OF_THREADS - 1].i = tmps[NB_OF_THREADS - 2].limit;
	tmps[NB_OF_THREADS - 1].limit = max;
	pthread_create(threads + NB_OF_THREADS - 1, NULL, &render_raytracing_part, tmps + NB_OF_THREADS - 1);
	for (size_t i = 0; i < NB_OF_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
}

static void	*render_raytracing_part(void *tmp_void)
{
	t_tmp		 	*tmp = tmp_void;
	unsigned int	color;

	while (tmp->i < tmp->limit)
	{
		color = vec_rgb_to_uint(render_pixel(tmp->engine, tmp->i));
		tmp->engine->ray_traced_image.address[tmp->i] = color;
		tmp->i++;
	}
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
	t_vector3f		result;
	t_vector3f		color;
	float			multiplier = 1.0f;
	int				bounces_per_pixel = 2;

	result = vector3f_create(0, 0, 0);
	for (int i = 0; i < bounces_per_pixel; i++)
	{
		ray_hit = calculate_ray_intersection(&ray, scene);
		if (!ray_hit.hit)
			return (vector3f_add(result, vector3f_multiply(scene->sky_color, multiplier)));

		// Lights

		// Color
		color = calculate_color(scene, ray_hit, multiplier);
		result = vector3f_add(result, color);
		multiplier *= 0.1f;
		ray.origin = vector3f_add(ray_hit.position, vector3f_multiply(ray_hit.normal, 0.0001f));
		ray.direction = reflect(ray.direction, ray_hit.normal);
	}
	return (result);
}
