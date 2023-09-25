/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 07:02:56 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 08:07:56 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "hooks.h"
#include "mlx_wrapper.h"
#include "ray_tracer_gui_api.h"
#include "render_frame.h"

#define NB_OF_MS_BEFORE_FULL_RESOLUTION 600

static bool	update_changed_scene(t_engine *engine, uint64_t *next_update_time,
				bool *was_rendered_at_full_resolution,
				const uint64_t current_time_in_ms);
static void	update_unchanged_scene(t_engine *engine, uint64_t next_update_time,
				bool *was_rendered_at_full_resolution,
				const uint64_t current_time_in_ms);

void	update_scene(t_engine *engine, const uint64_t start_time)
{
	static uint64_t			next_update_time = 0;
	static bool				was_rendered_at_full_resolution = false;
	const uint64_t			current_time_in_ms = ft_timeval_to_ms(
			ft_get_current_time());

	deal_keys(engine, start_time);
	update_placed_object_position(engine);
	if (update_changed_scene(engine, &next_update_time,
			&was_rendered_at_full_resolution, current_time_in_ms))
		return (update_placed_object_position(engine));
	update_placed_object_position(engine);
	update_unchanged_scene(engine, next_update_time,
		&was_rendered_at_full_resolution, current_time_in_ms);
}

static bool	update_changed_scene(t_engine *engine, uint64_t *next_update_time,
				bool *was_rendered_at_full_resolution,
				const uint64_t current_time_in_ms)
{
	if (deal_mouse(engine) || engine->pressed_keys_index > 0)
	{
		camera_recalculate_view(&engine->camera);
		camera_recalculate_rays(&engine->camera);
		engine->should_render_ray_tracing = true;
		engine->should_render_at_full_resolution = false;
		*was_rendered_at_full_resolution = false;
		*next_update_time = current_time_in_ms
			+ NB_OF_MS_BEFORE_FULL_RESOLUTION;
		engine->scene_changed = true;
		return (true);
	}
	if (engine->scene_changed)
	{
		engine->should_render_ray_tracing = true;
		engine->should_render_at_full_resolution = false;
		*was_rendered_at_full_resolution = false;
		*next_update_time = current_time_in_ms
			+ NB_OF_MS_BEFORE_FULL_RESOLUTION;
		return (true);
	}
	return (false);
}

static void	update_unchanged_scene(t_engine *engine,
				const uint64_t next_update_time,
				bool *was_rendered_at_full_resolution,
				const uint64_t current_time_in_ms)
{
	if (current_time_in_ms >= next_update_time)
	{
		if (*was_rendered_at_full_resolution)
			engine->should_render_ray_tracing = false;
		else if (engine->gui.hide_animation.hide_animation_finished)
		{
			engine->should_render_at_full_resolution = true;
			*was_rendered_at_full_resolution = true;
		}
	}
}
