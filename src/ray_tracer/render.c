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

#include <stdio.h>
#include <pthread.h>

#include "math/vector.h"
#include "ray_tracer/render.h"
#include "object.h"
#include "ray_tracer/shade.h"
#include "engine.h"
#include "threads.h"

static void		*render_raytracing_routine(void *arg_void);
static t_color	render_pixel(t_engine *engine, size_t ray_index);

///
/// \param engine
/// \param incrementer > 0
void	render_raytracing(t_engine *engine, const int incrementer)
{
	t_raytracing_routine_args	arg;

	arg.engine = engine;
	arg.current_line = 0;
	arg.incrementer = incrementer;
	start_threads(&arg, &render_raytracing_routine);
}

static void	*render_raytracing_routine(void *arg_void)
{
	t_raytracing_routine_args	*data;
	size_t						i;
	size_t						limit;

	data = get_routine_data(arg_void);
	mutex_lock(arg_void);
	while (data->current_line < data->engine->ray_traced_image.height)
	{
		i = data->current_line * data->engine->ray_traced_image.width;
		data->current_line += data->incrementer;
		mutex_unlock(arg_void);
		limit = i + data->engine->ray_traced_image.width;
		while (i < limit)
		{
			data->engine->raytraced_pixels.data[i] = render_pixel(data->engine,
					i);
			i += data->incrementer;
		}
		mutex_lock(arg_void);
	}
	mutex_unlock(arg_void);
	return (NULL);
}

static t_color	render_pixel(t_engine *engine, size_t ray_index)
{
	const t_ray	ray = engine->camera.rays[ray_index];
	t_vector3f	pixel_color;

	pixel_color = render_ray(ray, &engine->scene);
	pixel_color = calculate_post_processing_color(engine, pixel_color);
	pixel_color = vector3f_clamp(pixel_color, 0, 1);
	pixel_color = vector3f_multiply(pixel_color, 255);
	return (pixel_color);
}
