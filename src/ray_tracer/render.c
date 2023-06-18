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



void	render_raytracing(t_engine *minirt)
{
//	t_image			*img;
//	int				y;
//	int				x;
//	unsigned int	color;
//	float 			test;
//
//	img = &minirt->ray_traced_image;
//	y = 0;
//	x = 0;
//	while (y < img->height)
//	{
//		while (x < img->width)
//		{
////			color = vec_rgb_to_uint(render_pixel(minirt, x, y));
////			test = (float)(y * img->width + x) / (float) minirt->camera.viewport.number_of_pixels;
////			test = random_value((y * img->width + x));
//			test = float_rand(0, 1);
////			printf("%f\n", test);
//			test *= 255;
//			color = vec_rgb_to_uint(vector3f_create(test, test, test));
////			ft_printf("%d\n", (y * img->width + x));
////			if ((y * img->width + x) == 10)
////				exit(1);
//			put_pixel_on_image(img, y, x, color);
//			x++;
//		}
//		x = 0;
//		y++;
//	}
//	(void) render_raytracing_part;
	minirt->frame_count++;
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
	engine->path_accumulation[ray_index] = vector3f_add(engine->path_accumulation[ray_index], pixel_color);
	pixel_color = vector3f_divide(engine->path_accumulation[ray_index], (float)engine->frame_count);
	pixel_color = vector3f_clamp(pixel_color, 0, 1);
	pixel_color = vector3f_multiply(pixel_color, 255);
	return (pixel_color);
}

static t_vector3f	render_ray(t_ray ray, const t_scene *scene)
{
	t_hit			ray_hit;
	t_vector3f		incoming_light;
	t_vector3f		emitted_light;
	t_vector3f		ray_color;
	const int		bounces_per_pixel = 3;

	incoming_light = vector3f_create(0, 0, 0);
	ray_color = vector3f_create(1, 1, 1);
	for (int i = 0; i < bounces_per_pixel; i++)
	{
		ray_hit = calculate_ray_intersection(&ray, scene);
		if (!ray_hit.hit)
		{
			ray_color = vector3f_mult_vector3f(ray_color, scene->sky_color);
			incoming_light = vector3f_add(incoming_light, ray_color);
			return (incoming_light);
		}

		// Lights
		emitted_light = vector3f_multiply(ray_hit.object->material.emissive_color,
										  ray_hit.object->material.emissive_power);
		incoming_light = vector3f_add(incoming_light, vector3f_mult_vector3f(emitted_light, ray_color));
		ray_color = vector3f_mult_vector3f(ray_color,
										   ray_hit.object->material.albedo);

		t_vector3f	random_direction = vector3f_random(-1, 1);
//		while (vector3f_length(random_direction) <= 1.0f)
//			random_direction = vector3f_random(-1, 1);
		random_direction = vector3f_unit(random_direction);
		if (vector3f_dot(random_direction, ray_hit.normal) > 0)
			random_direction = vector3f_multiply(random_direction, -1);
		ray.origin = vector3f_add(ray_hit.position, vector3f_multiply(ray_hit.normal, 0.0001f));
//		ray.direction = reflect(ray.direction,
//								vector3f_add(ray_hit.normal, random_roughness));
		ray.direction = vector3f_unit(vector3f_add(ray_hit.normal, random_direction));
	}
	return (incoming_light);
}
