/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_icon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:38:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/12 10:38:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "engine.h"
#include "ray_tracer/render.h"
#include "threads.h"

#define PIXEL_DIVISION 2.f

static void			*render_raytracing_routine(void *arg_void);
static unsigned int	get_color(const t_engine *engine, int x, int y,
						unsigned int background_color);
static t_color		get_row_color(const t_engine *engine, int sub_y,
						t_vector2i position, int *missed_object_count);
static t_ray		get_ray(const t_engine *engine, float x, float y);

void	render_icon(t_engine *engine, const unsigned int background_color)
{
	t_render_raytraced_icon_routine_arg	arg;

	arg.engine = engine;
	arg.current_line = 0;
	arg.background_color = background_color;
	start_threads(&arg, &render_raytracing_routine);
}

static void	*render_raytracing_routine(void *arg_void)
{
	t_render_raytraced_icon_routine_arg	*data;
	int									x;
	int									y;
	unsigned int						*line;

	data = get_routine_data(arg_void);
	mutex_lock(arg_void);
	while (data->current_line < data->engine->ray_traced_image.height)
	{
		y = data->current_line;
		data->current_line++;
		mutex_unlock(arg_void);
		line = data->engine->ray_traced_image.address
			+ y * data->engine->ray_traced_image.width;
		x = data->engine->ray_traced_image.width;
		while (x--)
			line[x] = get_color(data->engine, x, y, data->background_color);
		mutex_lock(arg_void);
	}
	mutex_unlock(arg_void);
	return (NULL);
}

static unsigned int	get_color(const t_engine *engine, const int x, const int y,
						const unsigned int background_color)
{
	int		sub_y;
	t_color	color;
	int		missed_object_count;

	ft_bzero(&color, sizeof(color));
	missed_object_count = 0;
	sub_y = PIXEL_DIVISION;
	while (sub_y--)
		color = vector3f_add(color, get_row_color(engine, sub_y,
					(t_vector2i){x, y}, &missed_object_count));
	if (missed_object_count == PIXEL_DIVISION * PIXEL_DIVISION)
		return (background_color);
	color = vector3f_divide(color, PIXEL_DIVISION * PIXEL_DIVISION);
	color = vector3f_clamp(color, 0, 1);
	color = vector3f_multiply(color, 255);
	return (rgb_to_uint(color));
}

static t_color	get_row_color(const t_engine *engine, int sub_y,
					t_vector2i position, int *missed_object_count)
{
	t_ray	ray;
	int		sub_x;
	t_color	color;

	color = (t_color){0, 0, 0};
	sub_x = PIXEL_DIVISION;
	while (sub_x--)
	{
		ray = get_ray(engine,
				position.x + sub_x / PIXEL_DIVISION + 1.f \
					/ PIXEL_DIVISION / 2.f,
				engine->ray_traced_image.height - 1.f - position.y + sub_y \
					/ PIXEL_DIVISION + 1.f / PIXEL_DIVISION / 2.f);
		color = vector3f_add(color,
				render_ray_icon(ray, &engine->scene, missed_object_count));
	}
	return (color);
}

static t_ray	get_ray(const t_engine *engine, const float x, const float y)
{
	return (ray_create(engine->camera.position,
			get_ray_direction(&engine->camera, x, y)));
}
