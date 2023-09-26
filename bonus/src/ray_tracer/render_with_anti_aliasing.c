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

#include "engine.h"
#include "ray_tracer/render.h"
#include "threads.h"

#define PIXEL_DIVISION 2.f

static void			*render_raytracing_routine(void *arg_void);
static t_vector3f	get_antialiased_pixel(const t_engine *engine, int x, int y);
static t_ray		get_ray(const t_engine *engine, float x, float y);

void	render_anti_aliased_raytracing(t_engine *engine)
{
	t_raytracing_anti_aliasing_routine_args	arg;

	arg.engine = engine;
	arg.current_line = 0;
	start_threads(&arg, &render_raytracing_routine);
}

static void	*render_raytracing_routine(void *arg_void)
{
	t_raytracing_anti_aliasing_routine_args	*data;
	int										x;
	int										y;
	t_vector3f								*line;

	data = get_routine_data(arg_void);
	mutex_lock(arg_void);
	while (data->current_line < data->engine->ray_traced_image.height)
	{
		y = data->current_line;
		data->current_line++;
		mutex_unlock(arg_void);
		line = data->engine->raytraced_pixels.data
			+ y * data->engine->raytraced_pixels.width;
		x = data->engine->raytraced_pixels.width;
		while (x--)
			line[x] = get_antialiased_pixel(data->engine, x, y);
		mutex_lock(arg_void);
	}
	mutex_unlock(arg_void);
	return (NULL);
}

static t_vector3f	get_antialiased_pixel(const t_engine *engine, const int x,
						const int y)
{
	int		sub_y;
	int		sub_x;
	t_color	pixel;
	t_ray	ray;

	ft_bzero(&pixel, sizeof(pixel));
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
			pixel = vector3f_add(pixel, calculate_post_processing_color(engine,
						render_ray(ray, &engine->scene)));
		}
	}
	pixel = vector3f_divide(pixel, PIXEL_DIVISION * PIXEL_DIVISION);
	pixel = vector3f_clamp(pixel, 0, 1);
	return (vector3f_multiply(pixel, 255));
}

static t_ray	get_ray(const t_engine *engine, const float x, const float y)
{
	return (ray_create(engine->camera.position,
			get_ray_direction(&engine->camera, x, y)));
}
