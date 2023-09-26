/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:12:50 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 19:03:28 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <math.h>

#include "mlx.h"
#include "libft.h"

#include "engine.h"
#include "render_frame.h"
#include "ray_tracer/render.h"
#include "gui/utils.h"
#include "font/render.h"
#include "events.h"
#include "hooks.h"
#include "mlx_wrapper.h"
#include "object.h"
#include "interpolater.h"
#include "draw.h"

#define FPS_GOAL 45.f
#define FRAME_BEFORE_ADAPTION 20
#define DEFAULT_INCREMENTER_VALUE 2

static void			render_minirt_raytracing(t_engine *engine);
static int			adjust_incrementer(t_quality quality, int incrementer);
static int			get_incrementer(t_engine *engine);

int	render_frame(t_engine *engine)
{
	const struct timeval	start_time = ft_get_current_time();
	const uint64_t			start_time_ms = ft_timeval_to_ms(start_time);

	update_scene(engine, start_time_ms);
	render_minirt_raytracing(engine);
	put_image(engine, &engine->ray_traced_image, (t_vector2i){0, 0});
	render_bounding_box(engine);
	put_image(engine, &engine->bvh_image, (t_vector2i){0, 0});
	render_user_interface(engine, start_time_ms);
	render_screen_shot_animation(engine);
	if (IS_LINUX)
		mlx_put_image_to_window(engine->window.mlx, engine->window.window,
			engine->main_image.data, 0, 0);
	if (engine->should_render_ray_tracing)
		print_fps_counter(engine, start_time);
	engine->last_frame_start_time = start_time_ms;
	return (0);
}

static void	render_minirt_raytracing(t_engine *engine)
{
	int	incrementer;

	if (engine->should_render_ray_tracing == false)
		return ;
	if (engine->should_render_at_full_resolution && engine->antialiasing)
		render_anti_aliased_raytracing(engine);
	else if (engine->should_render_at_full_resolution)
	{
		render_raytracing(engine, engine->quality.min_reduction);
		if (engine->quality.min_reduction > 1)
			interpolate_ray_tracing(&engine->raytraced_pixels,
				engine->quality.min_reduction);
	}
	else
	{
		incrementer = get_incrementer(engine);
		render_raytracing(engine, incrementer);
		if (incrementer > 1)
			interpolate_ray_tracing(&engine->raytraced_pixels, incrementer);
	}
	engine->scene_changed = false;
	put_raytraced_pixels_to_raytraced_image(engine);
}

static int	get_incrementer(t_engine *engine)
{
	static int	incrementer = DEFAULT_INCREMENTER_VALUE;
	static int	fps_count = 0;
	static int	frame_count = 0;
	float		average_fps;

	if (engine->should_render_at_full_resolution)
		return (engine->quality.min_reduction);
	fps_count += engine->gui.fps.fps_nb;
	frame_count++;
	if (frame_count >= FRAME_BEFORE_ADAPTION)
	{
		average_fps = fps_count / (float)frame_count;
		if (average_fps <= FPS_GOAL * 0.66f)
			incrementer++;
		else if (incrementer > 1 && average_fps > FPS_GOAL * 1.33f)
			incrementer--;
		frame_count = 0;
		fps_count = 0;
	}
	incrementer = adjust_incrementer(engine->quality, incrementer);
	return (incrementer);
}

static int	adjust_incrementer(t_quality quality, int incrementer)
{
	if (incrementer >= quality.max_reduction)
		return (quality.max_reduction);
	if (incrementer <= quality.min_reduction)
		return (quality.min_reduction);
	return (incrementer);
}
